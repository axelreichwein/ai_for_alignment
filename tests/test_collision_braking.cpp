#include "collision_braking.h"
#include "obstacle_detection.h"
#include <gtest/gtest.h>

class DummyDetector : public ObstacleDetector {
public:
    DummyDetector(): ObstacleDetector(10.0) {}
    std::optional<Reading> scan(const std::vector<Reading>&) const override {
        return Reading{4.0,3.0};
    }
};

TEST(CollisionBrakingTest, TTCAboveThreshold_NoBrake) {
    DummyDetector det;
    BrakingController ctrl(det, 1.0);
    std::vector<ObstacleDetector::Reading> sensor;
    EXPECT_FALSE(ctrl.monitorAndBrake(sensor));
}

TEST(CollisionBrakingTest, TTCBelowThreshold_AppliesBrake) {
    DummyDetector det;
    BrakingController ctrl(det, 2.0);
    std::vector<ObstacleDetector::Reading> sensor;
    EXPECT_TRUE(ctrl.monitorAndBrake(sensor));
}