# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(smart-home-system)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add library for device classes
add_library(device_lib
    "src/devices/device.cpp"
    "src/devices/smart_light.cpp"
    "src/devices/thermostat.cpp"
    "src/devices/security_camera.cpp"
    "src/controllers/home_controller.cpp"
    "src/controllers/room_controller.cpp"
    "src/controllers/energy_monitor.cpp"
    
)

# add main executable
add_executable(smart_home_system
    "main.cpp"
)
target_link_libraries(smart_home_system device_lib)

# Add test executable
add_executable(test_devices
    "test/test_devices.cpp"
)
target_link_libraries(test_devices device_lib)
