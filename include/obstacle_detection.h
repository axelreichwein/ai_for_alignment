#pragma once
#include <vector>
#include <optional>
#include <utility>

class ObstacleDetector {
public:
    using Reading = std::pair<double,double>;
    explicit ObstacleDetector(double max_range = 10.0)
      : max_range_(max_range) {}
    std::optional<Reading> scan(const std::vector<Reading>& sensor_data) const;
private:
    double max_range_;
};