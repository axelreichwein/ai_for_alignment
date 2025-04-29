#include "obstacle_detection.h"
#include "collision_braking.h"
#include "driver_alert.h"
#include <gtest/gtest.h>
#include <sstream>

static std::vector<std::vector<ObstacleDetector::Reading>> generateSequence() {
    return {{}, {{6.0,2.0}}, {{4.0,3.0}}};
}

TEST(EbsSystemIntegrationTest, FullLoopBehavior) {
    ObstacleDetector det;
    BrakingController brk(det);
    DriverAlert alert;
    auto seq = generateSequence();
    std::ostringstream buf;
    std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
    bool brakeEngaged = false;
    for (auto& data : seq) {
        if (brk.monitorAndBrake(data)) {
            alert.notifyBraking();
            brakeEngaged = true;
            break;
        }
    }
    std::cout.rdbuf(old);
    std::string out = buf.str();
    EXPECT_TRUE(brakeEngaged);
    EXPECT_NE(out.find("***Brakes Engaged***"), std::string::npos);
    EXPECT_NE(out.find("ALERT: Automatic braking engaged!"), std::string::npos);
}