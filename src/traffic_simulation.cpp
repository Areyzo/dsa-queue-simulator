#include <raylib.h>
#include "traffic_simulation.hpp"
#include <fstream>
#include <istream>
#include <algorithm>

std::vector<Vehicle> vehicles;

void createVehicle() {
    Vehicle newVehicle;
    newVehicle.active = true;
    
    // Set the new dimensions for the vehicle
    newVehicle.rect = {0, 0, 18, 14};  // Width 18 and Height 14
    
    newVehicle.speed = 5;  // Reduced speed

    // Start the vehicle off-screen to the left
    newVehicle.rect.x = -newVehicle.rect.width;  // Position vehicle off-screen to the left

    // Assign vehicles to two lines in the center of the screen, with a smaller gap
    int lineChoice = GetRandomValue(0, 1); // 0 = top line, 1 = bottom line
    if (lineChoice == 0) {
        // Top line (centered horizontally, upper half of the screen, with reduced gap)
        newVehicle.rect.y = 400 - 50;
    } else {
        // Bottom line (centered horizontally, lower half of the screen, with reduced gap)
        newVehicle.rect.y = 400 -22;
    }

    // Assign a random color to the vehicle
    newVehicle.color = getRandomColor();
    
    vehicles.push_back(newVehicle);
}

void updateVehicles() {
    for (auto& vehicle : vehicles) {
        if (vehicle.active) {
            vehicle.rect.x += vehicle.speed;
            if (vehicle.rect.x > GetScreenWidth()) {
                vehicle.active = false; // Deactivate if off-screen to the right
            }
        }
    }

    // Remove inactive vehicles
    vehicles.erase(
        std::remove_if(vehicles.begin(), vehicles.end(), [](const Vehicle& v) { return !v.active; }),
        vehicles.end()
    );
}

Color getRandomColor() {
    int colorChoice = GetRandomValue(0, 2);  // 0 = Red, 1 = Blue, 2 = Yellow
    switch (colorChoice) {
        case 0: return RED;
        case 1: return BLUE;
        case 2: return YELLOW;
        default: return WHITE; // Default fallback color
    }
}