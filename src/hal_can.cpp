#include "hal_can.h"
#include "stm32f4xx_hal.h"
extern CAN_HandleTypeDef hcan;

void HAL_CAN_Init(uint32_t baudrate) {
    // HAL_CAN_Start(&hcan);
}

std::vector<ObstacleDetector::Reading> HAL_CAN_ReadObstacleData() {
    return {};
}

void HAL_CAN_SendBrakeCommand(uint8_t pressure) {
    CAN_TxHeaderTypeDef txh = {};
    uint8_t data[2] = {0x01, pressure};
    uint32_t txp;
    HAL_CAN_AddTxMessage(&hcan, &txh, data, &txp);
}

void HAL_CAN_SendHudAlert(const char* text) {
    CAN_TxHeaderTypeDef txh = {};
    uint8_t data[8] = {};
    size_t len = strlen(text);
    memcpy(data, text, len<8? len:8);
    uint32_t txp;
    HAL_CAN_AddTxMessage(&hcan, &txh, data, &txp);
}