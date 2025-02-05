// includes
#include "controllers/home_controller.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>

using namespace std;

// singleton instance
HomeController* HomeController::instance = nullptr; // nullptr

// singleton instance getter method
HomeController* HomeController::getInstance() { // getInstance
    if (instance == nullptr) { // if instance is null
        instance = new HomeController(); // then create a new instance
    } 
    return instance; // return instance
}

// function to add a device
void HomeController::addDevice(shared_ptr<Device> device) { // addDevice
    devices.push_back(device); // add device to vector
    cout << "Device added successfully.\n"; // print success message
}

// function to remove a device
void HomeController::removeDevice(const string& deviceID) { // removeDevice
    devices.erase( // erase device from vector
        remove_if(devices.begin(), devices.end(), // remove if condition is true
            [&deviceID](const auto& device) { // lambda function to check device ID
                return device->getDeviceID() == deviceID; // return true if device ID matches
            }
        ),
        devices.end() // end iterator
    );
}

// function to show the devices
void HomeController::showDevices() const { // showDevices
    cout << "Devices Available:\n"; // print header
    for (size_t i = 0; i < devices.size(); i++) { // loop through devices
        cout << i + 1 << ". " << devices[i]->getDeviceStatus() << "\n"; // print device status
    }
}

// function to display the home page
void HomeController::showMenu() const {
    cout << "\n=== Smart Home System ===\n" // print header
         << "1. List Available Devices\n"
         << "2. Control Device\n"
         << "3. Add Device\n"
         << "4. Remove Device\n"
         << "5. Exit\n"
         << "Please select an option: ";
}

// function to run the controller
void HomeController::run() { 
    int choice; // user choice variable
    while (true) { // infinite loop
        showMenu(); // show menu
        cin >> choice; // get user choice
        cin.ignore(); // ignore any extra characters in the input stream

        switch(choice) { // switch statement to handle user choice
            case 1: // list available devices
                showDevices(); // show devices
                break; 

            case 2: // control device switch statement
                if (devices.empty()) { // if no devices available
                    cout << "No devices available to control.\n"; // print error message
                    break;
                }
                showDevices(); // show devices
                cout << "Please select a device to control: "; // prompt user to select device
                size_t deviceNumber; // device number variable to store user input 
                cin >> deviceNumber; // get user input and store in deviceNumber
                if (deviceNumber > 0 && deviceNumber <= devices.size()) { // check if device number is valid 
                    handleDeviceControl(devices[deviceNumber - 1]); // call function to handle device control 
                } else { 
                    cout << "Invalid device number.\n";
                }
                break;

            case 3: { // add device switch statement
                cout << "Device Types:\n"
                     << "1. Smart Light\n"
                     << "2. Smart Thermostat\n"
                     << "Please select a device type: ";
                
                int deviceType; // device type variable to store user input
                cin >> deviceType; // get user input and store in deviceType
                cin.ignore(); // ignore any extra characters in the input stream

                // prompt user to enter device details
                string id, name, location; 
                cout << "Enter device ID: ";
                getline(cin, id);
                cout << "Enter device name: ";
                getline(cin, name);
                cout << "Enter device location: ";
                getline(cin, location);

                // if device type is 1 (Smart Light), create a SmartLight object
                if (deviceType == 1) {
                    addDevice(make_shared<SmartLight>(id, name, location));
                // if device type is 2 (Smart Thermostat), create a Thermostat object    
                } else if (deviceType == 2) {
                    addDevice(make_shared<Thermostat>(id, name, location));
                } else {
                    cout << "Invalid device type.\n";
                }
                break;
            }

            // remove device switch statement
            case 4:
                if (devices.empty()) { // if no devices available 
                    cout << "No devices available to remove.\n";
                    break;
                }
                showDevices(); // show devices
                cout << "Enter device ID to remove: "; // prompt user to enter device ID to remove
                {
                    string id; // device ID variable to store user input
                    cin >> id; // get user input and store in id
                    cin.ignore(); // ignore any extra characters in the input stream
                    removeDevice(id); // call function to remove device from vector 
                }
                break;

            // exit switch statement 
            case 5:
                cout << "Goodbye!\n";
                exit(0); // exit program
                break;

            default:
                cout << "Invalid choice. Please try again.\n"; // display error message if invalid choice
                break;
        }
    }
}

// function to handle device control
void HomeController::handleDeviceControl(const shared_ptr<Device> device) { 
    if (auto light = dynamic_pointer_cast<SmartLight>(device)) { // check if device is SmartLight 
        handleSmartLightControl(light); // call function to handle SmartLight control
        } else if (auto thermostat = dynamic_pointer_cast<Thermostat>(device)) { // check if device is SmartThermostat
        handleThermostatControl(thermostat); // call function to handle SmartThermostat control

    }
}

// function to handle SmartLight control
void HomeController::handleSmartLightControl(const shared_ptr<SmartLight> light) { 
    while (true) { // loop until user chooses to exit
        cout << "\n=== Smart Light Control ===\n"
             << "1. Turn On\n"
             << "2. Set Brightness\n"
             << "3. Set Color\n"
             << "4. Show Device Status\n"
             << "5. Back\n"
             << "Please select an option: ";

            
        int choice; // variable to store user choice
        cin >> choice; // get user input and store in choice

        // switch statement to handle user choice
        switch (choice) {
            case 1:
                if (light->getIsOn()) light->turnOff(); // turn off light if already on
                else light->turnOn(); // turn on light
                break; 

            // set brightness of light
            case 2: {
                cout << "Enter brightness level (0-100): ";
                int brightness;
                cin >> brightness;
                light->setBrightness(brightness); 
                break;
            }
            // set color of light
            case 3: {
                cout << "Enter color :";
                string color;
                cin.ignore(); // ignore newline left-over
                getline(cin, color);
                light->setColor(color);
                break;
            }
            // show device status
            case 4:
                cout << light->getDeviceStatus() << "\n";
                break;

            // exit
            case 5:
                return;
        }
    }
}

// function to handle SmartThermostat control
void HomeController::handleThermostatControl(const shared_ptr<Thermostat> thermostat) {
    while (true) {
        cout << "\n=== Thermostat Control ===\n"
             << "1. Turn On/Off\n"
             << "2. Set Temperature\n"
             << "3. Set Mode\n"
             << "4. Show Device Status\n"
             << "5. Back\n"
             << "Please select an option: ";

        // get user choice
        int choice;
        cin >> choice;

        // switch statement to handle user choice
        switch (choice) {
            // turn on/off thermostat
            case 1:
                if (thermostat->getIsOn()) thermostat->turnOff(); // turn off thermostat if already on
                else thermostat->turnOn(); // turn on thermostat if off
                break;

            // set temperature of thermostat
            case 2: {
                cout << "Enter temperature: ";
                float temperature; // declare float variable
                cin >> temperature;
                thermostat->setTemperature(temperature);
                break;
            }

            // set mode of thermostat
            case 3: {
                cout << "Enter mode (heating, cooling, auto): ";
                string mode; // declare string variable
                cin.ignore(); // ignore newline left-over
                getline(cin, mode); // read line input
                thermostat->setMode(mode);
                break;
            }

            // show device status of thermostat
            case 4:
                cout << thermostat->getDeviceStatus() << "\n"; // display device status of thermostat
                break;

            case 5:
                return;
            }
    }
}
