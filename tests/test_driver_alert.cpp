#include "driver_alert.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(DriverAlertTest, NotifyOutputsAlert) {
    DriverAlert alert;
    std::ostringstream buf;
    std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
    alert.notifyBraking();
    std::cout.rdbuf(old);
    std::string output = buf.str();
    EXPECT_NE(output.find("ALERT: Automatic braking engaged!"), std::string::npos);
}