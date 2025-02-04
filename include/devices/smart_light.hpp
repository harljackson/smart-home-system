#ifndef smart_light_hpp
#define smart_light_hpp

// includes
#include "devices/device.hpp"

// SmartLight class
class SmartLight : public Device {
    private:
        int brightness;
        string color;

    public:
        SmartLight(
            const string& id,
            const string& name,
            const string& location
        );

        // pure virtual functions
        void turnOn() override;
        void turnOff() override;
        double getPowerUsage() const override;
        string getDeviceStatus() const override;

        // additional functions
        void setBrightness(int brightness);
        void setColor(const string& color);
        int getBrightness() const;
        string getColor() const;

        #endif // smart_light_hpp
};

