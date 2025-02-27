#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <raylib.h>
#include <vector>

// Vehicle structure definition
struct Vehicle {
    Rectangle rect;
    Color color;
    bool active;
    float speed;
};

// Traffic light structure definition
struct TrafficLight {
    bool isGreen;      // true = green, false = red
    float timer;       // Timer for switching
    float switchTime;  // Time interval for switching light
};

// Function declarations
void createVehicle();
void updateVehicles();
Color getRandomColor();
void updateTrafficLight();
void drawTrafficLightIndicator();  // Declare this function

extern std::vector<Vehicle> vehicles;
extern TrafficLight trafficLight;

#endif
