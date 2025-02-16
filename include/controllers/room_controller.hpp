// room_controller.hpp
#ifndef room_controller_hpp
#define room_controller_hpp

// includes
#include <string>
#include <vector>
#include <memory>
#include "devices/device.hpp"

using namespace std;

// RoomController class
class RoomController {
    private:
    string roomName; // room name
    vector<shared_ptr<Device>> roomDevices; // devices in room


    public:
    // constructor
    RoomController(const string& name); // room name

    // room management
    void addDevice(shared_ptr<Device> device); // add device to room
    void removeDevice(const string& deviceID); // remove device from room
    void listDevices() const; // list all devices in room
    void turnAllDevicesOn(); // turn all devices on
    void turnAllDevicesOff(); // turn all devices off

    // getters
    string getRoomName() const; // get room name
    size_t getDeviceCount() const; // get number of devices in room
    bool hasDevice(const string& deviceId) const; // check if room has device
    vector<shared_ptr<Device>> getDevices() const; // get all devices in room
};

#endif