#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <raylib.h>
#include <stdbool.h>
#include <vector>

#define MAX_VEHICLES 10

typedef struct Vehicle {
    bool active;
    Rectangle rect;
    int speed;
    Color color;  // Added color to the Vehicle struct
} Vehicle;

extern std::vector<Vehicle> vehicles;

void createVehicle();
void updateVehicles();
Color getRandomColor();

#endif
