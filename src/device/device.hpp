// device.hpp

// created by: harley jackson

// include guard
#ifndef DEVICE_HPP
#define DEVICE_HPP

// include libraries
#include <string>

// using namespace
using namespace std;

// Device class
class Device {
    
    // private attributes
    private:
        // private attributes
        string deviceID; // device ID
        string deviceName; // device name
        string deviceLocation; // device location
        bool isOnline; // device online status
        double powerConsumption; // device power consumption
        double deviceTemperature; // device temperature

    // public methods
    public:
        // constructor for Device class
        Device(const string& id, const string& name, const string& location);

        // virtual destructor
        virtual ~Device() = default; 

        // virtual methods
        virtual void turnOn() = 0; // turn on device
        virtual void turnOff() = 0; // turn off device
        virtual void getStatus() const; // display device status
        virtual void calculatePowerConsumption() = 0; // calculate power consumption

        double getDeviceTemperature() const; // get device temperature
        void setDeviceTemperature(double temperature); // set device temperature
        
}