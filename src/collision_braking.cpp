#include "collision_braking.h"
#include <iostream>

BrakingController::BrakingController(const ObstacleDetector& det,
                                     double ttc_threshold)
  : detector_(det), ttc_threshold_(ttc_threshold) {}

double BrakingController::computeTTC(double distance, double speed) const {
    return (speed > 0.0) ? (distance / speed) : std::numeric_limits<double>::infinity();
}

bool BrakingController::monitorAndBrake(const std::vector<ObstacleDetector::Reading>& sensor_data) {
    auto obs = detector_.scan(sensor_data);
    if (obs) {
        double dist = obs->first;
        double speed = obs->second;
        double ttc  = computeTTC(dist, speed);
        if (ttc <= ttc_threshold_) {
            applyBrakes();
            return true;
        }
    }
    return false;
}

void BrakingController::applyBrakes() {
    std::cout << "***Brakes Engaged***\n";
}