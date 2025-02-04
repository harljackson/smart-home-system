#include <iostream>
#include "devices/device.hpp"
#include "devices/smart_light.hpp"

int main() {
    // create a smart light device
    SmartLight bedroomLight("001", "Bedroom Light", "Bedroom");

    // test functionality 
    cout << "Initial status: " << bedroomLight.getDeviceStatus() << endl;

    // turn on the smart light
    bedroomLight.turnOn();
    cout << "Status after turning on: " << bedroomLight.getDeviceStatus() << endl;

    // test brightness 
    bedroomLight.setBrightness(50);
    cout << "Brightness after setting: " << bedroomLight.getBrightness() << endl;

    // test color
    bedroomLight.setColor("Red");
    cout << "Color after setting: " << bedroomLight.getColor() << endl;

    // test power usage
    cout << "Power usage: " << bedroomLight.getPowerUsage() << endl;

    // test turn off
    bedroomLight.turnOff();
    cout << "Status after turning off: " << bedroomLight.getDeviceStatus() << endl;

    return 0;

}