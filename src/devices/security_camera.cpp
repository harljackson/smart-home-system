#include "devices/security_camera.hpp"
#include "controllers/home_controller.hpp"
#include <stdexcept>

// constructor
SecurityCamera::SecurityCamera(
    const std::string& id,
    const std::string& name,
    const std::string& location)
    : Device(id, name, location)
    , isRecording(false)
    , resolution("1080p")
    , angleRotation(0)
    , motionDetection(false)
{
    try {
        if (id.empty() || name.empty() || location.empty()) {
            throw std::invalid_argument("ID, name, and location cannot be empty");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error creating SecurityCamera: " << e.what() << std::endl;
        throw;
    }
}

// Override functions
void SecurityCamera::turnOn() {
    try {
        setIsOn(true);
        setPowerConsumption(0.5);  // 0.5W when running
    } catch (const std::exception& e) {
        std::cerr << "Error turning on camera: " << e.what() << std::endl;
        throw std::runtime_error("Failed to turn on camera");
    }
}

void SecurityCamera::turnOff() {
    try {
        setIsOn(false);
        isRecording = false;
        setPowerConsumption(0.0);
    } catch (const std::exception& e) {
        std::cerr << "Error turning off camera: " << e.what() << std::endl;
        throw std::runtime_error("Failed to turn off camera");
    }
}

double SecurityCamera::getPowerUsage() const {
    try {
        if (!getIsOn()) return 0.0;
        return isRecording ? 1.0 : 0.5;  // 1.0W when recording, 0.5W when just on
    } catch (const std::exception& e) {
        std::cerr << "Error getting power usage: " << e.what() << std::endl;
        throw std::runtime_error("Failed to get power usage");
    }
}

std::string SecurityCamera::getDeviceStatus() const {
    try {
        return "Security Camera " + getDeviceID() +
               " is " + (getIsOn() ? "on" : "off") +
               " [Recording: " + (isRecording ? "Yes" : "No") +
               ", Resolution: " + resolution +
               ", Rotation: " + std::to_string(angleRotation) +
               "°, Motion Detection: " + (motionDetection ? "On" : "Off") + "]";
    } catch (const std::exception& e) {
        std::cerr << "Error getting device status: " << e.what() << std::endl;
        throw std::runtime_error("Failed to get device status");
    }
}

// Camera specific functions
void SecurityCamera::startRecording() {
    try {
        if (!getIsOn()) {
            throw std::runtime_error("Camera must be on to start recording");
        }
        isRecording = true;
        setPowerConsumption(1.0);  // Increase power consumption when recording
    } catch (const std::exception& e) {
        std::cerr << "Error starting recording: " << e.what() << std::endl;
        throw;
    }
}

void SecurityCamera::stopRecording() {
    try {
        isRecording = false;
        if (getIsOn()) {
            setPowerConsumption(0.5);  // Return to standard power consumption
        }
    } catch (const std::exception& e) {
        std::cerr << "Error stopping recording: " << e.what() << std::endl;
        throw;
    }
}

void SecurityCamera::setResolution(const std::string& res) {
    try {
        if (res != "720p" && res != "1080p" && res != "4K") {
            throw std::invalid_argument("Invalid resolution. Use 720p, 1080p, or 4K");
        }
        resolution = res;
    } catch (const std::exception& e) {
        std::cerr << "Error setting resolution: " << e.what() << std::endl;
        throw;
    }
}

void SecurityCamera::setRotation(int angle) {
    try {
        if (angle < 0 || angle > 360) {
            throw std::invalid_argument("Rotation angle must be between 0 and 360 degrees");
        }
        angleRotation = angle;
    } catch (const std::exception& e) {
        std::cerr << "Error setting rotation: " << e.what() << std::endl;
        throw;
    }
}

void SecurityCamera::enableMotionDetection() {
    try {
        if (!getIsOn()) {
            throw std::runtime_error("Camera must be on to enable motion detection");
        }
        motionDetection = true;
    } catch (const std::exception& e) {
        std::cerr << "Error enabling motion detection: " << e.what() << std::endl;
        throw;
    }
}

void SecurityCamera::disableMotionDetection() {
    motionDetection = false;
}

// Getters
bool SecurityCamera::getIsRecording() const {
    return isRecording;
}

std::string SecurityCamera::getResolution() const {
    return resolution;
}

int SecurityCamera::getRotation() const {
    return angleRotation;
}

bool SecurityCamera::getMotionDetection() const {
    return motionDetection;
}

// Operator overloading
SecurityCamera& SecurityCamera::operator+(int angle) {
    try {
        setRotation((angleRotation + angle) % 360);
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Error rotating camera: " << e.what() << std::endl;
        return *this;
    }
}

std::ostream& operator<<(std::ostream& os, const SecurityCamera& camera) {
    try {
        os << camera.getDeviceStatus();
        return os;
    } catch (const std::exception& e) {
        std::cerr << "Error in stream output: " << e.what() << std::endl;
        return os;
    }
}
