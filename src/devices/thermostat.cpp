//includes
#include "devices/thermostat.hpp"
#include <cmath>

// constructor for thermostat class
Thermostat::Thermostat(const string& id, const string& name, const string& location)
: Device(id, name, location)
, temperature(20.0) // default temperature is 20.0 degrees celsius
, mode("auto") // default mode is auto
, desiredTemperature(20.0) // default desired temperature is 20.0 degrees celsius
{}

// turn on the thermostat
void Thermostat::turnOn() {
    setIsOn(true);
}

// turn off the thermostat
void Thermostat::turnOff() {
    setIsOn(false);
}

// set the temperature of the thermostat
double Thermostat::getPowerUsage() const {
    if (!getIsOn()) return 0.0;

    // calculate the power usage based on the temperature
    return fabs(desiredTemperature - temperature) * 0.1;
}

// get the status of the thermostat
string Thermostat::getDeviceStatus() const {
    return "Thermostat " + getDeviceID() + // get the device ID
    " is " + (getIsOn() ? "on" : "off") + // check if the thermostat is on or off ?
    " Current Temperature: " + to_string(temperature) + "C, " + // get the temperature value and convert it to string
    " Desired Temperature: " + to_string(desiredTemperature) + "C, " + // get the desired temperature value and
    " Mode: " + mode + ")"; // get the mode of the thermostat
}

// set the temperature of the thermostat
void Thermostat::setTemperature(float temp) {
    if (temp >= 0 && temp <= 50) { // check if the temperature is between 0 and 50 degrees celsius
        temperature = temp; // set the temperature to the given value
    }
}

// set the mode of the thermostat
void Thermostat::setMode(const string& newMode) {
    if (newMode == "heating" || newMode == "cooling" || newMode == "auto") {
        mode = newMode; // set the mode to the given value
    }
}

// get the temperature of the thermostat
float Thermostat::getTemperature() const {
    return temperature; // return the temperature value
}

// get mode of the thermostat
string Thermostat::getMode() const {
    return mode; // return the mode value
}

// get the desired temperature of the thermostat
float Thermostat::getDesiredTemperature() const {
    return desiredTemperature; // return the desired temperature value
}

// set the desired temperature of the thermostat
void Thermostat::setDesiredTemperature(float temp) {
    if (temp >= 0 && temp <= 50) { // check if the temperature is between 0 and 50 degrees celsius
        desiredTemperature = temp; // set the desired temperature to the given value
    }
}