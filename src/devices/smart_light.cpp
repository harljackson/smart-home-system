// includes
#include "devices/smart_light.hpp"
#include <stdexcept> // exception handling

// constructor
SmartLight::SmartLight(
    const string& id, // unique identifier
    const string& name, // name of the device
    const string& location) // location of the device
try : Device(id, name, location), // call the Device constructor
    brightness(0), // initialize brightness to 0
    color("White") // initialize color to white
{
    if (id.empty() || name.empty() || location.empty()) {
        throw invalid_argument("ID, name, and location cannot be empty");
    }
} catch (const exception& e) {
    cerr << "Error creating SmartLight: " << e.what() << endl;
    throw; // Re-throw the exception
}

// methods for controlling the light
// turn the light on
void SmartLight::turnOn() {
    try {
        setIsOn(true); // set the status to on (true)
        setPowerConsumption(0.1); // set the power consumption to 0.1 W
    } catch (const exception& e) {
        cerr << "Error turning on light: " << e.what() << endl;
        throw runtime_error("Failed to turn on light");
    }
}

// turn the light off
void SmartLight::turnOff() { 
    try {
        setIsOn(false); // set the status to off (false)
        brightness = 0; // set the brightness to 0
        setPowerConsumption(0.0); // set the power consumption to 0 W
    } catch (const exception& e) {
        cerr << "Error turning off light: " << e.what() << endl;
        throw runtime_error("Failed to turn off light");
    }
}

// get the power usage when the light is powered on
double SmartLight::getPowerUsage() const { 
    try {
        return powerConsumption;
    } catch (const exception& e) {
        cerr << "Error getting power usage: " << e.what() << endl;
        throw runtime_error("Failed to get power usage");
    }
}

// get the device status
string SmartLight::getDeviceStatus() const {
    try {
        return "Smart Light " + getDeviceID() + // get the device ID
        " is " + (getIsOn() ? "on" : "off") + // check if the light is on or off
        " with brightness " + to_string(brightness) + // get the brightness value
        "%, " + "and color " + getColor(); // get the color
    } catch (const exception& e) {
        cerr << "Error getting device status: " << e.what() << endl;
        throw runtime_error("Failed to get device status");
    }
}

// set the brightness of the light device
void SmartLight::setBrightness(int level) {
    try {
        if (level < 0 || level > 100) {
            throw invalid_argument("Brightness must be between 0 and 100");
        }
        brightness = level; // set the brightness to the given level
        
        // power consumption increases with brightness
        double power = level * 0.001; 
        setPowerConsumption(power);
    } catch (const invalid_argument& e) {
        cerr << "Invalid brightness value: " << e.what() << endl;
        throw;
    } catch (const exception& e) {
        cerr << "Error setting brightness: " << e.what() << endl;
        throw runtime_error("Failed to set brightness");
    }
}

// set the color of the light device
void SmartLight::setColor(const string& newColor) { 
    try {
        if (newColor.empty()) {
            throw invalid_argument("Color cannot be empty");
        }
        color = newColor; // set the color to the given color
    } catch (const invalid_argument& e) {
        cerr << "Invalid color value: " << e.what() << endl;
        throw;
    } catch (const exception& e) {
        cerr << "Error setting color: " << e.what() << endl;
        throw runtime_error("Failed to set color");
    }
}

// get the brightness of the light device
int SmartLight::getBrightness() const {
    try {
        return brightness; // return the brightness value
    } catch (const exception& e) {
        cerr << "Error getting brightness: " << e.what() << endl;
        throw runtime_error("Failed to get brightness");
    }
}

// get the color of the light device
string SmartLight::getColor() const {
    try {
        return color; // return the color value
    } catch (const exception& e) {
        cerr << "Error getting color: " << e.what() << endl;
        throw runtime_error("Failed to get color");
    }
}

// add operator overloading for the SmartLight class
SmartLight& SmartLight::operator+(int brightnessIncrement) {
    try {
        if (brightnessIncrement < 0) {
            throw invalid_argument("Brightness increment cannot be negative");
        }
        setBrightness(brightness + brightnessIncrement);
        return *this;
    } catch (const invalid_argument& e) {
        cerr << "Invalid brightness increment: " << e.what() << endl;
        throw;
    } catch (const exception& e) {
        cerr << "Error in brightness increment: " << e.what() << endl;
        throw runtime_error("Failed to increment brightness");
    }
}

// stream operator overloading
ostream& operator<<(ostream& os, const SmartLight& light) {
    try {
        os << light.getDeviceStatus();
        return os;
    } catch (const exception& e) {
        cerr << "Error in stream output: " << e.what() << endl;
        throw runtime_error("Failed to output device status");
    }
}
