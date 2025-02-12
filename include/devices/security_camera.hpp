#ifndef security_camera_hpp
#define security_camera_hpp

// includes
#include "devices/device.hpp"
#include <iostream>

using namespace std;

// SecurityCamera class
class SecurityCamera : public Device {
    private:
        // private members
        bool isRecording; // is the camera currently recording?
        string resolution; // resolution of the camera (e.g. 1080p, 4K)
        int angleRotation; // rotation of the camera (e.g. 90 degrees)
        bool motionDetection; // motion detection status

    public:
        // constructor
        SecurityCamera(
            const string& id, // device id
            const string& name, // name of device
            const string& location // location of device
        );

        // override virtual functions
        void turnOn() override; // turn on the camera
        void turnOff() override; // turn off the camera
        double getPowerUsage() const override; // get power consumption of the camera
        string getDeviceStatus() const override; // get device status

        // camera specific functions
        void startRecording(); // start recording
        void stopRecording(); // stop recording
        void setResolution(const string& res); // set resolution of the camera
        void setRotation(int angle); // set angle of the camera
        void enableMotionDetection(); // enable motion detection
        void disableMotionDetection(); // disable motion detection

        // getters
        bool getIsRecording() const; // get recording status
        string getResolution() const; // get resolution of the camera
        int getRotation() const; // get angle of the camera
        bool getMotionDetection() const; // get motion detection status

        // operator overloading
        SecurityCamera& operator+(int angle); // rotate camera
        friend ostream& operator<<(ostream& os, const SecurityCamera& camera);

    };

    #endif
