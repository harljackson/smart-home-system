#include "controllers/home_controller.hpp"
#include "devices/security_camera.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <limits>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::getline;
using std::shared_ptr;
using std::make_shared;
using std::exception;
using std::numeric_limits;

// Singleton instance
HomeController* HomeController::instance = nullptr;

// Singleton instance getter method
HomeController* HomeController::getInstance() {
    if (instance == nullptr) {
        instance = new HomeController();
    } 
    return instance;
}

// Function to add a device
void HomeController::addDevice(shared_ptr<Device> device) {
    devices.push_back(device);
    cout << "Device added successfully.\n";
}

// Function to remove a device
void HomeController::removeDevice(const string& deviceID) {
    auto initialSize = devices.size();
    devices.erase(
        remove_if(devices.begin(), devices.end(),
            [&deviceID](const auto& device) {
                return device->getDeviceID() == deviceID;
            }
        ),
        devices.end()
    );
    if (devices.size() < initialSize) {
        cout << "Device removed successfully.\n";
    } else {
        cout << "Device not found.\n";
    }
}

// Function to show the devices
void HomeController::showDevices() const {
    if (devices.empty()) {
        cout << "No devices available.\n";
        return;
    }
    cout << "\nDevices Available:\n";
    for (size_t i = 0; i < devices.size(); i++) {
        cout << i + 1 << ". " << devices[i]->getDeviceStatus() << "\n";
    }
}

// Function to display the home page
void HomeController::showMenu() const {
    cout << "\n=== Smart Home System ===\n"
         << "1. List Available Devices\n"
         << "2. Control Device\n"
         << "3. Add Device\n"
         << "4. Remove Device\n"
         << "5. Exit\n"
         << "Please select an option: ";
}

// Function to run the controller
void HomeController::run() {
    cout << "Welcome to Smart Home System!\n";
    
    while (true) {
        showMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        try {
            switch(choice) {
                case 1:
                    showDevices();
                    break;

                case 2: {
                    if (devices.empty()) {
                        cout << "No devices available to control.\n";
                        break;
                    }
                    showDevices();
                    cout << "Please select a device to control (1-" << devices.size() << "): ";
                    size_t deviceNumber;
                    if (cin >> deviceNumber && deviceNumber > 0 && deviceNumber <= devices.size()) {
                        handleDeviceControl(devices[deviceNumber - 1]);
                    } else {
                        cout << "Invalid device number.\n";
                    }
                    cin.ignore();
                    break;
                }

                case 3: {
                    cout << "Device Types:\n"
                         << "1. Smart Light\n"
                         << "2. Smart Thermostat\n"
                         << "3. Security Camera\n"
                         << "Please select a device type: ";
                    
                    int deviceType;
                    if (!(cin >> deviceType)) {
                        cout << "Invalid input.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    cin.ignore();

                    string id, name, location;
                    cout << "Enter device ID: ";
                    getline(cin, id);
                    cout << "Enter device name: ";
                    getline(cin, name);
                    cout << "Enter device location: ";
                    getline(cin, location);

                    try {
                        switch (deviceType) {
                            case 1:
                                addDevice(make_shared<SmartLight>(id, name, location));
                                break;
                            case 2:
                                addDevice(make_shared<Thermostat>(id, name, location));
                                break;
                            case 3:
                                addDevice(make_shared<SecurityCamera>(id, name, location));
                                break;
                            default:
                                cout << "Invalid device type.\n";
                        }
                    } catch (const exception& e) {
                        cerr << "Error creating device: " << e.what() << endl;
                    }
                    break;
                }

                case 4: {
                    if (devices.empty()) {
                        cout << "No devices available to remove.\n";
                        break;
                    }
                    showDevices();
                    cout << "Enter device ID to remove: ";
                    string id;
                    getline(cin, id);
                    removeDevice(id);
                    break;
                }

                case 5:
                    cout << "Thank you for using Smart Home System. Goodbye!\n";
                    return;

                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

// Function to handle device control
void HomeController::handleDeviceControl(const shared_ptr<Device> device) {
    if (auto light = dynamic_pointer_cast<SmartLight>(device)) {
        handleSmartLightControl(light);
    } else if (auto thermostat = dynamic_pointer_cast<Thermostat>(device)) {
        handleThermostatControl(thermostat);
    } else if (auto camera = dynamic_pointer_cast<SecurityCamera>(device)) {
        handleSecurityCameraControl(camera);
    }
}

// Function to handle SmartLight control
void HomeController::handleSmartLightControl(const shared_ptr<SmartLight> light) {
    while (true) {
        cout << "\n=== Smart Light Control ===\n"
             << "1. Turn On/Off\n"
             << "2. Set Brightness\n"
             << "3. Set Color\n"
             << "4. Show Device Status\n"
             << "5. Quick Increase Brightness (+15%)\n"
             << "6. Back\n"
             << "Please select an option: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    if (light->getIsOn()) {
                        light->turnOff();
                        cout << "Light turned off.\n";
                    } else {
                        light->turnOn();
                        cout << "Light turned on.\n";
                    }
                    cout << *light << "\n";
                    break;
                }

                case 2: {
                    cout << "Enter brightness level (0-100): ";
                    int brightness;
                    if (cin >> brightness) {
                        light->setBrightness(brightness);
                        cout << *light << "\n";
                    } else {
                        cout << "Invalid brightness value.\n";
                        cin.clear();
                    }
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                case 3: {
                    cout << "Enter color: ";
                    string color;
                    getline(cin, color);
                    light->setColor(color);
                    cout << *light << "\n";
                    break;
                }

                case 4:
                    cout << *light << "\n";
                    break;

                case 5: {
                    *light = *light + 15;
                    cout << "Increased brightness by 15%\n";
                    cout << *light << "\n";
                    break;
                }

                case 6:
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

// Function to handle Thermostat control
void HomeController::handleThermostatControl(const shared_ptr<Thermostat> thermostat) {
    while (true) {
        cout << "\n=== Thermostat Control ===\n"
             << "1. Turn On/Off\n"
             << "2. Set Temperature\n"
             << "3. Set Mode\n"
             << "4. Show Device Status\n"
             << "5. Back\n"
             << "Please select an option: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    if (thermostat->getIsOn()) {
                        thermostat->turnOff();
                        cout << "Thermostat turned off.\n";
                    } else {
                        thermostat->turnOn();
                        cout << "Thermostat turned on.\n";
                    }
                    cout << thermostat->getDeviceStatus() << "\n";
                    break;
                }

                case 2: {
                    cout << "Enter temperature: ";
                    float temperature;
                    if (cin >> temperature) {
                        thermostat->setTemperature(temperature);
                        cout << thermostat->getDeviceStatus() << "\n";
                    } else {
                        cout << "Invalid temperature value.\n";
                        cin.clear();
                    }
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                case 3: {
                    cout << "Enter mode (heating/cooling/auto): ";
                    string mode;
                    getline(cin, mode);
                    thermostat->setMode(mode);
                    cout << thermostat->getDeviceStatus() << "\n";
                    break;
                }

                case 4:
                    cout << thermostat->getDeviceStatus() << "\n";
                    break;

                case 5:
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

// Function to handle SecurityCamera control
void HomeController::handleSecurityCameraControl(const shared_ptr<SecurityCamera> camera) {
    while (true) {
        cout << "\n=== Security Camera Control ===\n"
             << "1. Turn On/Off\n"
             << "2. Start/Stop Recording\n"
             << "3. Set Resolution\n"
             << "4. Rotate Camera\n"
             << "5. Toggle Motion Detection\n"
             << "6. Show Device Status\n"
             << "7. Back\n"
             << "Please select an option: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    if (camera->getIsOn()) {
                        camera->turnOff();
                        cout << "Camera turned off.\n";
                    } else {
                        camera->turnOn();
                        cout << "Camera turned on.\n";
                    }
                    cout << *camera << "\n";
                    break;
                }

                case 2: {
                    if (camera->getIsRecording()) {
                        camera->stopRecording();
                        cout << "Recording stopped.\n";
                    } else {
                        camera->startRecording();
                        cout << "Recording started.\n";
                    }
                    cout << *camera << "\n";
                    break;
                }

                case 3: {
                    cout << "Enter resolution (720p/1080p/4K): ";
                    string res;
                    getline(cin, res);
                    camera->setResolution(res);
                    cout << "Resolution set to " << res << "\n";
                    cout << *camera << "\n";
                    break;
                }

                case 4: {
                    cout << "Enter rotation angle (0-360): ";
                    int angle;
                    if (cin >> angle) {
                        camera->setRotation(angle);
                        cout << "Camera rotated to " << angle << " degrees\n";
                    } else {
                        cout << "Invalid angle value.\n";
                        cin.clear();
                    }
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    cout << *camera << "\n";
                    break;
                }

                case 5: {
                    if (camera->getMotionDetection()) {
                        camera->disableMotionDetection();
                        cout << "Motion detection disabled.\n";
                    } else {
                        camera->enableMotionDetection();
                        cout << "Motion detection enabled.\n";
                    }
                    cout << *camera << "\n";
                    break;
                }

                case 6:
                    cout << *camera << "\n";
                    break;

                case 7:
                    return;

                default:
                    cout << "Invalid option.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}
