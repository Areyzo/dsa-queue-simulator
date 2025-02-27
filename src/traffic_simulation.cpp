#include <raylib.h>
#include "traffic_simulation.hpp"
#include <fstream>
#include <istream>
#include <algorithm>

std::vector<Vehicle> vehicles;
TrafficLight trafficLight = {false, 0.0f, 3.0f};  // Initializing traffic light to red

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
            // If the light is red, stop vehicles in the middle
            if (!trafficLight.isGreen && vehicle.rect.x >= 350 && vehicle.rect.x <= 450) {
                vehicle.speed = 0;  // Stop vehicle
            } else if (trafficLight.isGreen && vehicle.rect.x < GetScreenWidth()) {
                vehicle.speed = 5;  // Move vehicle when green
            }

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

// Function to update the state of the traffic light
void updateTrafficLight() {
    trafficLight.timer += GetFrameTime();
    if (trafficLight.timer >= trafficLight.switchTime) {
        trafficLight.isGreen = !trafficLight.isGreen;  // Toggle traffic light state
        trafficLight.timer = 0.0f;
    }
}

// Function to draw the traffic light indicator on the screen
void drawTrafficLightIndicator() {
    int x = 700; // X position of the traffic light
    int y = 350; // Y position of the traffic light

    // Draw a smaller rectangle for the traffic light
    DrawRectangle(x, y, 40, 100, DARKGRAY);  // Adjusted size for the traffic light

    // Draw the green or red light (no yellow now)
    Color lightColor = trafficLight.isGreen ? GREEN : RED;
    DrawRectangle(x + 5, y + 10, 30, 30, lightColor);  // Top light (Green/Red)

    // Optional: Label indicating the current state
    const char* stateText = trafficLight.isGreen ? "Green" : "Red";
    DrawText(stateText, x + 5, y + 75, 20, WHITE);  // Smaller text
}
