// includes
#include "devices/smart_light.hpp"

// constructor
SmartLight::SmartLight(
    const string& id, // unique identifier
    const string& name, // name of the device
    const string& location) // location of the device

    // initialize the device
    : Device(id, name, location) // call the Device constructor
    , brightness(0) // initialize brightness to 0
    , color("White") // initialize color to white
    {} 

// methods for controlling the light
// turn the light on
void SmartLight::turnOn() {
    setIsOn(true); // set the status to on (true)
    setPowerConsumption(0.1); // set the power consumption to 0.1 W
}
// turn the light off
void SmartLight::turnOff() { 
    setIsOn(false); // set the status to off (false)
    brightness = 0; // set the brightness to 0
    setPowerConsumption(0.0); // set the power consumption to 0 W
}

// get the power usage when the light is powered on
double SmartLight::getPowerUsage() const { 
    return powerConsumption;
}

// set the brightness of the light device
string SmartLight::getDeviceStatus() const {
    return "Smart Light " + getDeviceID() + // get the device ID
    " is " + (getIsOn() ? "on" : "off") + // check if the light is on or off ?
    " with brightness " + to_string(brightness) + // get the brightness value and convert it to string
    "%, " + "and color " + getColor(); // get the color of the light device
}

// set the brightness of the light device
void SmartLight::setBrightness(int level) {
    if (level >= 0 && level <= 100) { // check if the level is between 0 and 100
        brightness = level; // set the brightness to the given level
        setPowerConsumption(level * 0.001); // calculate the power consumption based on the brightness level
    }
}

// set the color of the light device
void SmartLight::setColor(const string& color) { 
    this->color = color; // set the color to the given color
}

// get the brightness of the light device
int SmartLight::getBrightness() const {
    return brightness; // return the brightness value
}

// get the color of the light device
string SmartLight::getColor() const {
    return color; // return the color value
}

