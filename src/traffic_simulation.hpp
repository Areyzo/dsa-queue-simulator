#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <raylib.h>
#include <vector>

// Enum for directions
enum Direction {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3
};

// Vehicle struct declaration
struct Vehicle {
    Rectangle rect;
    bool active;
    int speed;
    Color color;
    Direction direction; // Store direction
};

// TrafficLight struct declaration
struct TrafficLight {
    Rectangle rect;
    bool isGreen;
};

// Function prototypes
void createVehicle();
void updateVehicles();
Color getRandomColor();
void drawTrafficLightIndicator();
void updateTrafficLight();

extern std::vector<Vehicle> vehicles;
extern TrafficLight trafficLights[4];
extern int currentLight; // Track which traffic light is green

#endif // TRAFFIC_SIMULATION_HPP
