#include "obstacle_detection.h"
#include <algorithm>

std::optional<ObstacleDetector::Reading>
ObstacleDetector::scan(const std::vector<Reading>& sensor_data) const {
    std::optional<Reading> nearest;
    for (auto& r : sensor_data) {
        double dist = r.first;
        if (dist <= max_range_) {
            if (!nearest || dist < nearest->first) {
                nearest = r;
            }
        }
    }
    return nearest;
}