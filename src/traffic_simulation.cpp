#include <raylib.h>
#include "traffic_simulation.hpp"
#include <fstream>
#include <istream>
#include <algorithm>

std::vector<Vehicle> vehicles;

TrafficLight trafficLight = {{250, 230, 50, 100}, false}; // Traffic light position moved to the left

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
        newVehicle.rect.y = 400 - 22;
    }

    // Assign a random color to the vehicle
    newVehicle.color = getRandomColor();

    vehicles.push_back(newVehicle);
}

void updateVehicles() {
    for (auto& vehicle : vehicles) {
        if (vehicle.active) {
            // Stop vehicles behind the midpoint if the light is red
            if (!trafficLight.isGreen && vehicle.rect.x + vehicle.rect.width > GetScreenWidth() / 2) {
                continue; // Do not move the vehicle
            }
            
            // If the light is green, allow vehicle to move
            if (trafficLight.isGreen) {
                vehicle.rect.x += vehicle.speed;
            }

            // If the vehicle goes off-screen to the right, deactivate it
            if (vehicle.rect.x > GetScreenWidth()) {
                vehicle.active = false;
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

void drawTrafficLightIndicator() {
    // Draw the traffic light indicator
    DrawRectangle(trafficLight.rect.x, trafficLight.rect.y, trafficLight.rect.width, trafficLight.rect.height, DARKGRAY);

    // Draw the red light
    DrawCircle(trafficLight.rect.x + trafficLight.rect.width / 2, trafficLight.rect.y + 20, 15, trafficLight.isGreen ? DARKGRAY : RED);

    // Draw the green light
    DrawCircle(trafficLight.rect.x + trafficLight.rect.width / 2, trafficLight.rect.y + 50, 15, trafficLight.isGreen ? GREEN : DARKGRAY);

    // Draw labels for lanes
    DrawText("Priority Lane", 100, 350, 20, RED);  // Priority lane label
    DrawText("Normal Lane", 100, 380, 20, BLUE);   // Normal lane label
}

void updateTrafficLight() {
    static int frameCounter = 0;
    frameCounter++;

    // The traffic light turns green after 10 vehicles in the priority lane
    int priorityLaneVehicleCount = std::count_if(vehicles.begin(), vehicles.end(), [](const Vehicle& v) {
        return v.rect.y == 400 - 50;  // Top lane is considered the priority lane
    });

    // Toggle light every 180 frames (3 seconds at 60 FPS) or if there are 10 or more vehicles in the priority lane
    if (priorityLaneVehicleCount >= 10 || frameCounter % 180 == 0) {
        trafficLight.isGreen = !trafficLight.isGreen;
        frameCounter = 0;  // Reset frame counter
    }
}
