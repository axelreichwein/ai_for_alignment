#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "obstacle_detection.h"
#include "collision_braking.h"
#include "driver_alert.h"
#include "hal_can.h"

using SensorMsg = std::vector<ObstacleDetector::Reading>;
using AlertMsg  = bool;

static TaskHandle_t    SensorTaskHandle;
static TaskHandle_t    ControlTaskHandle;
static TaskHandle_t    AlertTaskHandle;
static QueueHandle_t   SensorQueue;
static QueueHandle_t   AlertQueue;
static ObstacleDetector detector(10.0);
static BrakingController braker(detector, 2.0);
static DriverAlert       alerter;

void SensorTask(void* pv) {
    const TickType_t period = pdMS_TO_TICKS(10);
    SensorMsg msg;
    while (true) {
        msg = HAL_CAN_ReadObstacleData();
        xQueueOverwrite(SensorQueue, &msg);
        vTaskDelay(period);
    }
}

void ControlTask(void* pv) {
    SensorMsg incoming;
    AlertMsg  alertFlag;
    while (true) {
        if (xQueueReceive(SensorQueue, &incoming, portMAX_DELAY) == pdTRUE) {
            if (braker.monitorAndBrake(incoming)) {
                HAL_CAN_SendBrakeCommand(100);
                alertFlag = true;
                xQueueSend(AlertQueue, &alertFlag, 0);
            }
        }
    }
}

void AlertTask(void* pv) {
    AlertMsg flag;
    while (true) {
        if (xQueueReceive(AlertQueue, &flag, portMAX_DELAY) == pdTRUE && flag) {
            HAL_CAN_SendHudAlert("BRAKING");
            flag = false;
        }
    }
}

int main() {
    HAL_Timer_Init();
    HAL_CAN_Init(500000);
    SensorQueue = xQueueCreate(4, sizeof(SensorMsg));
    AlertQueue  = xQueueCreate(4, sizeof(AlertMsg));
    xTaskCreate(SensorTask,  "Sensor",  configMINIMAL_STACK_SIZE, nullptr, 2, &SensorTaskHandle);
    xTaskCreate(ControlTask, "Control", configMINIMAL_STACK_SIZE, nullptr, 3, &ControlTaskHandle);
    xTaskCreate(AlertTask,   "Alert",   configMINIMAL_STACK_SIZE, nullptr, 1, &AlertTaskHandle);
    vTaskStartScheduler();
    while (1) {}
    return 0;
}