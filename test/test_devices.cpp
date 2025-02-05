#include <iostream>
#include <iomanip>
#include "devices/device.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"

// define a function for separating output
void printSeparator() { 
    cout << "\n" << string(50, '=') << "\n"; // print a line of = signs
}

// function for section header
void printSectionHeader(const string& header) { // pass the header as a parameter
    printSeparator(); // call the printSeparator function
    cout << "  " << header << "\n"; // print the header with some added spacing
    printSeparator(); // call the printSeparator function
}


// test the Thermostat class
void testThermostat() {
    Thermostat livingRoomThermostat("W02", "Living Room Thermostat", "Living Room");

    // print thermostat header
    printSectionHeader("SMART THERMOSTAT DEVICE TEST");

    // initial state of the thermostat
    cout << "\n[INFO] Device Information:\n"
         << "  ID: " << livingRoomThermostat.getDeviceID() << "\n"
         << "  Name: " << livingRoomThermostat.getDeviceName() << "\n"
         << "  Location: " << livingRoomThermostat.getDeviceLocation() << "\n";

    // initial state test 
    printSectionHeader("INITIAL STATE");
    cout << "\n[STATUS] " << livingRoomThermostat.getDeviceStatus() << "\n";

    // test turning on and setting temperature
    printSectionHeader("THERMOSTAT POWERED ON");
    livingRoomThermostat.turnOn(); // turn on the thermostat
    cout << "\n[POWER] " << livingRoomThermostat.getDeviceStatus() << "\n";

    // test changing temperature
    printSectionHeader("CHANGING TEMPERATURE");
    livingRoomThermostat.setTemperature(25); // set the temperature to 25 degrees
    cout << "\n[TEMP] Desired Temperature: " << livingRoomThermostat.getDesiredTemperature() << "C\n"
    << "  Current Temperature: " << livingRoomThermostat.getTemperature() << "C\n" // print the current temperature
    << "  Status: " << livingRoomThermostat.getDeviceStatus() << "\n";

    // test changing mode
    printSectionHeader("CHANGING MODE");
    livingRoomThermostat.setMode("heating"); // set the mode to heating
    cout << "\n[MODE] Mode: " << livingRoomThermostat.getMode() << "\n"
    << "  Status: " << livingRoomThermostat.getDeviceStatus() << "\n";

    // test power usage calculation
    printSectionHeader("POWER USAGE");
    cout << "\n[ENERGY] Power Usage: " << fixed << setprecision(3)
    << livingRoomThermostat.getPowerUsage() << " W\n";

    // test turning off
    printSectionHeader("THERMOSTAT POWERED OFF");
    livingRoomThermostat.turnOff(); // turn off the thermostat
    cout << "\n[POWER] " << livingRoomThermostat.getDeviceStatus() << "\n";

}



int main() {
    // create a smart light device
    SmartLight bedroomLight("001", "Bedroom Light", "Bedroom");

    // print program header
    printSectionHeader("SMART LIGHT DEVICE TEST");

    // initial state of the smart light device
    cout << "\n[INFO] Device Information:\n"
         << "  ID: " << bedroomLight.getDeviceID() << "\n"
         << "  Name: " << bedroomLight.getDeviceName() << "\n"
         << "  Location: " << bedroomLight.getDeviceLocation() << "\n";

    
    // initial state
    printSectionHeader("INITIAL STATE");
    cout << "\n[STATUS] " << bedroomLight.getDeviceStatus() << "\n";

    // test turning on
    printSectionHeader("LIGHT POWERED ON");
    bedroomLight.turnOn();
    cout << "\n[POWER] " << bedroomLight.getDeviceStatus() << "\n";

    // test brightness 
    printSectionHeader("BRIGHTNESS ADJUSTMENT");
    bedroomLight.setBrightness(50);
    cout << "\n[BRIGHTNESS] Brightness: " << bedroomLight.getBrightness() << "%\n"
    << "  Status: " << bedroomLight.getDeviceStatus() << "\n";

    // test color
    printSectionHeader("COLOR ADJUSTMENT");
    bedroomLight.setColor("Warm White");
    cout << "\n[COLOR] Color: " << bedroomLight.getColor() << "\n"
    << "  Status: " << bedroomLight.getDeviceStatus() << "\n";

    // test power usage
    printSectionHeader("POWER USAGE");
    cout << "\n[ENERGY] Power Usage: " << fixed << setprecision(3) << bedroomLight.getPowerUsage() << " W\n";

    // test turning off
    printSectionHeader("LIGHT POWERED OFF");
    bedroomLight.turnOff();
    cout << "\n[POWER] " << bedroomLight.getDeviceStatus() << "\n";

    // test thermostat
    printSectionHeader("THERMOSTAT TEST");
    testThermostat();
    printSeparator();

    // complete
    printSectionHeader("TEST COMPLETE");
    printSeparator();
    cout << "\n[COMPLETE] Test complete.\n";
    printSeparator();

    return 0;






}