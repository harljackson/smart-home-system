#include "devices/device.hpp"

// default constructor
Device::Device() 
    : deviceID("") // default device id
    , deviceName("") // default name
    , deviceLocation("") // default location
    , isOn(false) // default value for isOn is false
    , powerConsumption(0.0) // default value for power consumption

{} // end constructor


// parameterized constructor
Device::Device(const string& id, const string& name, const string& location)
    : deviceID(id) // set device id
    , deviceName(name) // set device name
    , deviceLocation(location) // set device location
    , isOn(false) // default value for isOn is false
    , powerConsumption(0.0) // default value for power consumption
{} // end constructor


// getter for device ID
string Device::getDeviceID() const {
    return deviceID;
}

// getter for device name
string Device::getDeviceName() const {
    return deviceName;
}

// getter for device location
string Device::getDeviceLocation() const {
    return deviceLocation;
}

// getter for isOn status
bool Device::getIsOn() const {
    return isOn;
}


// setter for device location
void Device::setDeviceLocation(const string& newLocation) {
    deviceLocation = newLocation;
}

// setter for device name
void Device::setDeviceName(const string& newName) {
    deviceName = newName;
}

// setter for device status
void Device::setIsOn(bool status) {
    isOn = status;
}

// setter for power consumption
void Device::setPowerConsumption(double consumption) {
    powerConsumption = consumption;
}

