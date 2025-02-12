#ifndef HOME_CONTROLLER_HPP
#define HOME_CONTROLLER_HPP

#include <memory>
#include <vector>
#include "devices/device.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"
#include "devices/security_camera.hpp"

class HomeController {
private:
    static HomeController* instance;
    std::vector<std::shared_ptr<Device>> devices;
    HomeController() = default;

    // Device control handlers
    void handleSmartLightControl(const std::shared_ptr<SmartLight> light);
    void handleThermostatControl(const std::shared_ptr<Thermostat> thermostat);
    void handleSecurityCameraControl(const std::shared_ptr<SecurityCamera> camera);

public:
    static HomeController* getInstance();
    void addDevice(std::shared_ptr<Device> device);
    void removeDevice(const std::string& deviceId);
    void showDevices() const;
    void showMenu() const;
    void handleDeviceControl(const std::shared_ptr<Device> device);
    void run();
};

#endif
