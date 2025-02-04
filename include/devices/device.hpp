// device.hpp
#ifndef smart_home_devices_device_hpp
#define smart_home_devices_device_hpp

// include libraries
#include <string>
#include <iostream>

// using namespace
using namespace std;

// Device class
class Device {

    protected: // protected members are accessible within the class and its derived classes

        string deviceID; // unique identifier for the device
        string deviceName; // name of the device
        string deviceLocation; // location of the device
        bool isOn; // flag to indicate if the device is on or off
        double powerConsumption; // power consumption of the device

    
    public: // public members are accessible from outside the class

        Device(); // default constructor
        Device(const string& id, const string& name, const string& location); // parameterized constructor

        // virtual destructor important for inheritance
        virtual ~Device() = default; 

        // pure virtual functions for derived classes
        virtual void turnOn() = 0; // turn the device on
        virtual void turnOff() = 0; // turn the device off
        virtual double getPowerUsage() const = 0; // get the power usage of the device
        virtual string getDeviceStatus() const = 0; // get the status of the device

        // getters for device properties and status
        string getDeviceID() const; // get the device ID
        string getDeviceName() const; // get the device name
        string getDeviceLocation() const; // get the device location
        bool getIsOn() const; // get the isOn flag

        // setters for device properties and status
        void setDeviceLocation(const string& newLocation); // set the device location
        void setDeviceName(const string& newName); // set the device name

    // protected methods for derived classes
    protected:
        // set the device status
        void setIsOn(bool status);
        void setPowerConsumption(double power);

        
};

#endif // smart_home_devices_device_hpp

