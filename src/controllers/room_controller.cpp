#include "controllers/room_controller.hpp"
#include <iostream>
#include <algorithm>

// using statements
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::remove_if;
using std::any_of;

RoomController::RoomController(const string& name) : roomName(name) {}

// add device to room
void RoomController::addDevice(shared_ptr<Device> device) {
    if (!hasDevice(device->getDeviceID())) {
        roomDevices.push_back(device);
        cout << "Device " << device->getDeviceID() << " added to " << roomName << endl;
    } else {
        cout << "Device already exists in this room." << endl;
    }
}

// remove device from room
void RoomController::removeDevice(const string& deviceID) {
    auto initialSize = roomDevices.size();
    roomDevices.erase(
        remove_if(roomDevices.begin(), roomDevices.end(),
                  [&deviceID](const auto& device) {
                      return device->getDeviceID() == deviceID;
                  }),
        roomDevices.end());

    if (roomDevices.size() < initialSize) {
        cout << "Device " << deviceID << " removed from " << roomName << endl;
    } else {
        cout << "Device not found in this room." << endl;
    }
}

// list all devices in room
void RoomController::listDevices() const {
    cout << "\nDevices in " << roomName << " (" << roomDevices.size() << " devices):" << endl;
    if (roomDevices.empty()) {
        cout << "No devices in this room." << endl;
        return;
    }
    for (size_t i = 0; i < roomDevices.size(); ++i) {
        cout << i + 1 << ". " << roomDevices[i]->getDeviceStatus() << endl;
    }
}

// turn all devices on
void RoomController::turnAllDevicesOn() {
    cout << "Turning on all devices in " << roomName << "..." << endl;
    for (auto& device : roomDevices) {
        try {
            device->turnOn();
        } catch (const std::exception& e) {
            std::cerr << "Error turning on device " << device->getDeviceID() << ": " << e.what() << endl;
            throw std::runtime_error("Failed to turn on device");
        }
    }
}

// turn all devices off
void RoomController::turnAllDevicesOff() {
    cout << "Turning off all devices in " << roomName << "..." << endl;
    for (auto& device : roomDevices) {
        try {
            device->turnOff();
        } catch (const std::exception& e) {
            std::cerr << "Error turning off device " << device->getDeviceID() << ": " << e.what() << endl;
            throw std::runtime_error("Failed to turn off device");
        }
    }
}

// get room name
string RoomController::getRoomName() const {
    return roomName;
}

// get number of devices in room
size_t RoomController::getDeviceCount() const {
    return roomDevices.size();
}

// check if room has device by ID
bool RoomController::hasDevice(const string& deviceID) const {
    return any_of(roomDevices.begin(), roomDevices.end(),
                  [&deviceID](const auto& device) {
                      return device->getDeviceID() == deviceID;
                  });
}

// vector of devices in room
vector<shared_ptr<Device>> RoomController::getDevices() const {
    return roomDevices;
}
