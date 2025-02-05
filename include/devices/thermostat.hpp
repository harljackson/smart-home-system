#ifndef thermostat_hpp
#define thermostat_hpp

// includes
#include "devices/device.hpp"


using namespace std;

// Thermostat class
class Thermostat : public Device { // inherit from Device class
    private: 
        // private members
        float temperature; // temperature of the room
        string mode; // heating, cooling or auto
        float desiredTemperature; // desired temperature of the room

    public:
        // constructor
        Thermostat(
            const string& id, // unique identifier
            const string& name, // name of the device
            const string& location // location of the device
        );

        // override functions from Device class
        void turnOn() override; // override turnOn function from Device class
        void turnOff() override; // override turnOff function from Device class
        double getPowerUsage() const override; // override getPowerUsage function from Device class
        string getDeviceStatus() const override; // override getDeviceStatus function from Device class

        // additional functions
        void setTemperature(float temp); // set the temperature of the room
        void setMode(const string& newMode); // set the mode of the thermostat
        void setDesiredTemperature(float temp); // set the desired temperature of the room
        

        // getters
        float getTemperature() const; // get the temperature of the room
        string getMode() const; // get the mode of the thermostat
        float getDesiredTemperature() const; // get the desired temperature of the room

};

#endif // thermostat_hpp

