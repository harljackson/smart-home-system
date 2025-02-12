#ifndef smart_light_hpp
#define smart_light_hpp

// includes
#include "devices/device.hpp"
#include <iostream> 

using std::string;
using std::ostream;

// SmartLight class
class SmartLight : public Device {
    // private members
    private:
        int brightness; // 0-100
        string color; // white, red, green, blue

    // public methods
    public: 
        SmartLight( // constructor
            const string& id, // unique identifier
            const string& name, // name of the device
            const string& location // location of the device
        );

        // override virtual functions
        void turnOn() override; // turn on the light device
        void turnOff() override; // turn off the light device
        double getPowerUsage() const override; // get the power usage
        string getDeviceStatus() const override; // get the device status

        // smartlight specific functions
        void setBrightness(int brightness); // set the brightness
        void setColor(const string& color); // set the color
        int getBrightness() const; // get the brightness
        string getColor() const; // get the color

        // operator overloading declarations
        SmartLight& operator+(int brightnessIncrement); // brightness increment operator overloading
        friend ostream& operator<<(ostream& os, const SmartLight& light); // print operator overloading
};

#endif // smart_light_hpp
