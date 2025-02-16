// includes 
#include "controllers/energy_monitor.hpp"
#include "devices/device.hpp"
#include <iostream>
#include <iomanip>

// using statements
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

// initialize instance to nullptr
EnergyMonitor* EnergyMonitor::instance = nullptr; 

// get energy monitor instance and create it if it doesn't exist
EnergyMonitor* EnergyMonitor::getInstance() {
    if (!instance) {
        instance = new EnergyMonitor();
    }
    return instance;
}

// record usage for a device
void EnergyMonitor::recordUsage(
    const std::string& deviceID, double usage) {
        // record usage for device and update total usage
        currentUsage[deviceID] = usage;
        totalUsage[deviceID] += usage;
}

// get current usage for a device 
double EnergyMonitor::getCurrentUsage(
    const std::string& deviceID) const {
        // return current usage for device
        auto it = currentUsage.find(deviceID);
        return (it != currentUsage.end()) ? it->second : 0.0;
}

// get total usage for a device
double EnergyMonitor::getTotalUsage(
    const std::string& deviceID) const {
        // return total usage for device
        auto it = totalUsage.find(deviceID);
        return (it != totalUsage.end()) ? it->second : 0.0;
}

// get total system usage
double EnergyMonitor::getTotalSystemUsage() const {
    // initialize total usage to 0
    double total = 0.0;
    // iterate through devices and sum total usage
    for (const auto& pair : totalUsage) {
        total += pair.second;
    }
    return total;
}

// display current usage for all devices
void EnergyMonitor::displayCurrentUsage() const {
    cout << "\n=== Current Device Usage ===\n";
    if (currentUsage.empty()) {
        cout << "No devices currently in use.\n";
        return;
    }

    // set precision for output to 2 decimal places
    double totalPower = 0.0;
    cout << fixed << setprecision(2);

    // for each device, display power usage
    for (const auto& pair : currentUsage) {
        cout << "Device: " << pair.first << " | Usage: " << pair.second << " watts\n";
        totalPower += pair.second;
    }

    cout << "Total Current Power Usage: " << totalPower << " W\n";
}

// display total usage for all devices being used
void EnergyMonitor::displayTotalUsage() const {
    cout << "\n=== Total Device Usage ===\n";
    // check if there are devices in use
    if (totalUsage.empty()) {
        cout << "No devices currently in use.\n";
        return;
    }

    // set precision for output to 2 decimal places
    double totalEnergy = 0.0;
    cout << fixed << setprecision(2);

    // for each device, display total energy usage
    for (const auto& pair : totalUsage) {
        cout << "Device: " << pair.first << " | Usage: " << pair.second << " watts\n";
        totalEnergy += pair.second;
    }

    cout << "Total Energy Consumed: " << totalEnergy << " W\n";
}

// generate energy report for all devices
void EnergyMonitor::generateReport() const {
    cout << "\n=== Energy Report ===\n";
    cout << fixed << setprecision(2);

    // current power usage
    cout << "\nCurrent Power Usage:\n";
    cout << "---------------------\n";
    displayCurrentUsage();

    // total energy consumption
    cout << "\nTotal Energy Consumption:\n";
    cout << "-------------------------\n";
    displayTotalUsage();

    // system summary 
    cout << "\nSystem Summary:\n";
    cout << "---------------\n";
    cout << "Total Devices Monitored: " << currentUsage.size() << "\n";
    cout << "Total System Power Usage: " << getTotalSystemUsage() << " W\n";
}
