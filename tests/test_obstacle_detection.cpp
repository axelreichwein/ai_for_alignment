#include "obstacle_detection.h"
#include <gtest/gtest.h>

TEST(ObstacleDetectionTest, NoObstaclesInRange) {
    ObstacleDetector det(10.0);
    std::vector<ObstacleDetector::Reading> data = {{12.0,1.0},{15.0,2.0}};
    auto res = det.scan(data);
    EXPECT_FALSE(res.has_value());
}

TEST(ObstacleDetectionTest, FindsNearestObstacle) {
    ObstacleDetector det(10.0);
    std::vector<ObstacleDetector::Reading> data = {{8.0,1.5},{5.0,2.0},{9.0,0.5}};
    auto res = det.scan(data);
    ASSERT_TRUE(res.has_value());
    EXPECT_DOUBLE_EQ(res->first, 5.0);
    EXPECT_DOUBLE_EQ(res->second, 2.0);
}