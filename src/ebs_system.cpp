#include "obstacle_detection.h"
#include "collision_braking.h"
#include "driver_alert.h"

// Simulated sensor read stub
std::vector<ObstacleDetector::Reading> readSensors() {
    return {{4.0, 3.0}};
}

int main() {
    ObstacleDetector detector;
    BrakingController braker(detector);
    DriverAlert alerter;

    auto data = readSensors();
    if (braker.monitorAndBrake(data)) {
        alerter.notifyBraking();
    }
    return 0;
}