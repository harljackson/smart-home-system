// includes
#include "devices/smart_light.hpp"

SmartLight::SmartLight(
    const string& id,
    const string& name,
    const string& location)

    : Device(id, name, location)
    , brightness(0)
    , color("White")
    {} 

void SmartLight::turnOn() {
    setIsOn(true);
    setPowerConsumption(0.1);
}

void SmartLight::turnOff() {
    setIsOn(false);
    brightness = 0;
}

double SmartLight::getPowerUsage() const {
    return powerConsumption;
}

string SmartLight::getDeviceStatus() const {
    return "Smart Light " + getDeviceID() +
    " is " + (getIsOn() ? "on" : "off") +
    " with brightness " + to_string(brightness) +
    "%, " + "and color " + getColor();
}

void SmartLight::setBrightness(int level) {
    if (level >= 0 && level <= 100) {
        brightness = level;
        setPowerConsumption(level * 0.001);
        
    }
}

void SmartLight::setColor(const string& color) {
    this->color = color;
}

int SmartLight::getBrightness() const {
    return brightness;
}

string SmartLight::getColor() const {
    return color;
}

