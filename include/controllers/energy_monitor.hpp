#ifndef energy_monitor_hpp
#define energy_monitor_hpp

// includes
#include <map>
#include <string>
#include <vector>
#include "devices/device.hpp"

// EnergyMonitor class
class EnergyMonitor {
    // private members
    private:

    // current and total usage of devices in the system
    std::map<std::string, double> currentUsage;
    std::map<std::string, double> totalUsage;
    static EnergyMonitor* instance; 
    EnergyMonitor() = default; 

    public:
    // get instance
    static EnergyMonitor* getInstance();

    // energy tracking 
    void recordUsage(const std::string& deviceName, double usage);
    double getCurrentUsage(const std::string& deviceID) const;
    double getTotalUsage(const std::string& deviceID) const;
    double getTotalSystemUsage() const;

    // energy reporting
    void displayCurrentUsage() const;
    void displayTotalUsage() const;
    void generateReport() const;
};

#endif