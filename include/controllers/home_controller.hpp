#ifndef home_controller_hpp
#define home_controller_hpp

// includes
#include <iostream>
#include <vector>
#include <memory>

#include "devices/device.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"

using namespace std;

// HomeController class
class HomeController {
    private:
    vector<shared_ptr<Device>> devices; // vector of devices
    static HomeController* instance; // Singleton instance
    HomeController() = default; // private constructor 

    // public methods
    public:
    static HomeController* getInstance(); // Singleton getter

    // device mananger
    void addDevice(shared_ptr<Device> device); // add device
    void removeDevice(const string& deviceID); // remove device
    shared_ptr<Device> getDevice(const string& deviceID); // get device
    void showDevices() const; // show devices

    // user interface
    void showMenu() const; // show device menu
    void run(); // run controller

    private:

    // helper functions
    void handleDeviceControl(const shared_ptr<Device> device); // handle device control
    void handleSmartLightControl(const shared_ptr<SmartLight> smartLight); // handle smart light control
    void handleThermostatControl(const shared_ptr<Thermostat> thermostat); // handle thermostat control
};

#endif