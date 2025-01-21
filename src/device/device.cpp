// device.cpp

// created by harley jackson

// include libraries
#include "device.hpp"
#include <iostream>

// using namespace
using namespace std;


// constructor for Device class
Device::Device(const string& id, const string& name, const string& location) {
    deviceID = id;
    deviceName = name;
    deviceLocation = location;
    isOnline = false;
    powerConsumption = 0.0;
    deviceTemperature = 0.0;
}

// device status function 
void Device::turnOn() {
    isOnline = true;
    cout << deviceName << " is now online." << endl;
}