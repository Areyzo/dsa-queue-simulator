#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <vector>
#include <raylib.h>

// Structure to define a vehicle
struct Vehicle {
    Rectangle rect;
    Color color;
    bool active;
    float speed;
    int direction;  // 0: Straight, 1: Left, 2: Right
    bool isPriorityLane;  // Flag to indicate if the vehicle is in the priority lane
};

// Structure for traffic light
struct TrafficLight {
    Rectangle rect;
    bool isGreen;  // true: Green, false: Red
};

// Declare the functions that are used in traffic simulation
void createVehicle();
void updateVehicles();
Color getRandomColor();
void updateTrafficLight();
void drawTrafficLightIndicator();

// Declare the external vector of vehicles and the priority lane counter
extern std::vector<Vehicle> vehicles;
extern TrafficLight trafficLight;
extern int priorityLaneVehicleCount;  // Counter for vehicles in the priority lane

#endif
