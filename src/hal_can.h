#pragma once
#include <vector>
#include "obstacle_detection.h"

void HAL_CAN_Init(uint32_t baudrate);
std::vector<ObstacleDetector::Reading> HAL_CAN_ReadObstacleData();
void HAL_CAN_SendBrakeCommand(uint8_t pressure);
void HAL_CAN_SendHudAlert(const char* text);