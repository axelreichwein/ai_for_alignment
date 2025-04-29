#pragma once
#include "obstacle_detection.h"

class BrakingController {
public:
    explicit BrakingController(const ObstacleDetector& detector,
                               double ttc_threshold = 2.0);
    bool monitorAndBrake(const std::vector<ObstacleDetector::Reading>& sensor_data);
private:
    double computeTTC(double distance, double speed) const;
    void applyBrakes();
    const ObstacleDetector& detector_;
    double ttc_threshold_;
};