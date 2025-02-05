#include <iostream>
#include "devices/device.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"
#include "controllers/home_controller.hpp"

using namespace std;

int main() {
    cout << "Smart home system starting up..." << endl;

    // Create a smart light device instance
    HomeController* controller = HomeController::getInstance();
    
    // add some devices
    cout << "Adding devices...\n";

    // add some devices to the controller
    controller->addDevice(make_shared<SmartLight>("SL1", "Bedroom Light", "Bedroom"));
    controller->addDevice(make_shared<SmartLight>("SL2", "Living Room Light", "Living Room"));
    controller->addDevice(make_shared<Thermostat>("ST1", "Living Room Thermostat", "Living Room"));

    cout << "Devices added...\n";

    // run the control loop
    cout << "Control loop running...\n";
    cout << "Test devices added and running..." << endl;

    // run the controller
    controller->run();

    return 0;
}