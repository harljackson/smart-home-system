#include "controllers/home_controller.hpp"
#include "devices/security_camera.hpp"
#include "devices/smart_light.hpp"
#include "devices/thermostat.hpp"
#include "controllers/room_controller.hpp"
#include "controllers/energy_monitor.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <limits>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::getline;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;
using std::unique_ptr;
using std::exception;
using std::numeric_limits;
using std::vector;

// singleton instance
HomeController* HomeController::instance = nullptr;

// singleton instance getter method
HomeController* HomeController::getInstance() {
    if (instance == nullptr) {
        instance = new HomeController();
    }
    return instance;
}

// function to add a device
void HomeController::addDevice(shared_ptr<Device> device) {
    devices.push_back(device);
    cout << "Device added successfully.\n";
}

// function to remove a device
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

// function to show the devices
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
         << "5. Room Management\n"
         << "6. Energy Monitoring\n"
         << "7. Exit\n"
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
            switch (choice) {
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

                case 5: { // Room Management
                    cout << "Room Management:\n"
                         << "1. Add Room\n"
                         << "2. Remove Room\n"
                         << "3. List Rooms\n"
                         << "4. Assign Device to Room\n"
                         << "5. Back\n"
                         << "Please select an option: ";

                    int roomOption;
                    if (!(cin >> roomOption)) {
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number.\n";
                        break;
                    }
                    cin.ignore();

                    switch (roomOption) {
                        case 1: {
                            cout << "Enter room name: ";
                            string roomName;
                            getline(cin, roomName);
                            addRoom(roomName);
                            break;
                        }
                        case 2: {
                            cout << "Enter room name to remove: ";
                            string roomName;
                            getline(cin, roomName);
                            removeRoom(roomName);
                            break;
                        }
                        case 3: {
                            listRooms();
                            break;
                        }
                        case 4: {
                            cout << "Enter device ID: ";
                            string deviceId;
                            getline(cin, deviceId);
                            cout << "Enter room name: ";
                            string roomName;
                            getline(cin, roomName);
                            assignDeviceToRoom(deviceId, roomName);
                            break;
                        }
                        case 5:
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                    }
                    break;
                }

                case 6:
                    handleEnergyMonitoring();
                    break;

                case 7:
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

// Function to assign device to room
void HomeController::assignDeviceToRoom(const string& deviceId, const string& roomName) {
    // Find the device with the given ID
    auto deviceIt = find_if(devices.begin(), devices.end(),
        [&deviceId](const auto& device) {
            return device->getDeviceID() == deviceId;
        }
    );

    if (deviceIt == devices.end()) {
        cout << "Device not found.\n";
        return;
    }

    // Find the room with the given name
    auto roomIt = find_if(rooms.begin(), rooms.end(),
        [&roomName](const auto& room) {
            return room->getRoomName() == roomName;
        }
    );

    if (roomIt == rooms.end()) {
        cout << "Room not found.\n";
        return;
    }

    // Add the device to the room
    (*roomIt)->addDevice(*deviceIt);
    cout << "Device " << deviceId << " assigned to room " << roomName << "\n";
}

// Function to add a room
void HomeController::addRoom(const string& roomName) {
    // Check if room already exists
    auto it = find_if(rooms.begin(), rooms.end(),
        [&roomName](const auto& room) {
            return room->getRoomName() == roomName;
        }
    );

    if (it != rooms.end()) {
        cout << "Room already exists.\n";
        return;
    }

    // Create a new room and add it to the list
    rooms.push_back(make_unique<RoomController>(roomName));
    cout << "Room " << roomName << " added successfully.\n";
}

// Function to remove a room
void HomeController::removeRoom(const string& roomName) {
    auto initialSize = rooms.size();
    rooms.erase(
        std::remove_if(rooms.begin(), rooms.end(),
            [&roomName](const auto& room) {
                return room->getRoomName() == roomName;
            }
        ),
        rooms.end()
    );

    if (rooms.size() < initialSize) {
        cout << "Room " << roomName << " removed successfully.\n";
    } else {
        cout << "Room not found.\n";
    }
}

// Function to list all rooms
void HomeController::listRooms() const {
    if (rooms.empty()) {
        cout << "No rooms available.\n";
        return;
    }

    cout << "\nAvailable Rooms:\n";
    for (const auto& room : rooms) {
        cout << "- " << room->getRoomName() << ":\n";
        room->listDevices();
    }
}
// Function to handle Energy Monitoring
void HomeController::handleEnergyMonitoring() {
    auto monitor = EnergyMonitor::getInstance();
    int choice; 

    // Energy Monitoring Menu
    while (true) {
        cout << "\n=== Energy Monitoring ===\n"
             << "1. View Current Usage\n"
             << "2. View Total Consumption\n"
             << "3. Generate Energy Report\n"
             << "4. Back\n"
             << "Please select an option: ";

        // Read user input and validate it
        if (!(cin >> choice)) {
            cin.clear(); // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Check if choice is within valid range
        if (choice < 1 || choice > 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear rest of the line
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input

        // Process the valid selection
        switch (choice) {
            case 1:
                monitor->displayCurrentUsage();
                break;
            case 2:
                monitor->displayTotalUsage();
                break;
            case 3:
                monitor->generateReport();
                break;
            case 4:
                return;
        }

        cout << "\nPress Enter to continue...";
        cin.get(); // Wait for the user to press Enter
    }
}
