#include <raylib.h>
#include "traffic_simulation.hpp"
#include <fstream>
#include <istream>
#include <algorithm>

std::vector<Vehicle> vehicles;

TrafficLight trafficLights[4] = {
    {{250, 230, 50, 100}, false},  // Left
    {{475, 480, 50, 100}, false},  // Right
    {{475, 230, 50, 100}, false},  // Top
    {{250, 480, 50, 100}, false}   // Bottom
};

int currentLight = 0; // Index to track which traffic light is green

// Function to create a new vehicle
void createVehicle() {
    Vehicle newVehicle;
    newVehicle.active = true;
    newVehicle.rect = {0, 0, 18, 14};  // Width 18 and Height 14
    newVehicle.speed = 5;

    // Check if the corresponding traffic light is green
    if (!trafficLights[LEFT].isGreen && !trafficLights[RIGHT].isGreen &&
        !trafficLights[TOP].isGreen && !trafficLights[BOTTOM].isGreen) {
        return;  // If no light is green, do not spawn vehicles
    }

    int direction = -1;

    // Choose direction based on the green light (spawn vehicles only where the light is green)
    if (trafficLights[LEFT].isGreen) {
        direction = LEFT;
        newVehicle.rect.x = -newVehicle.rect.width;
        newVehicle.rect.y = (GetRandomValue(0, 1) == 0) ? 350 : 380;
    } 
    else if (trafficLights[RIGHT].isGreen) {
        direction = RIGHT;
        newVehicle.rect.x = GetScreenWidth();
        newVehicle.rect.y = (GetRandomValue(0, 1) == 0) ? 400 : 430;
        newVehicle.speed = -5;
    } 
    else if (trafficLights[TOP].isGreen) {
        direction = TOP;
        newVehicle.rect.x = (GetRandomValue(0, 1) == 0) ? 400 : 430;
        newVehicle.rect.y = -newVehicle.rect.height;
    } 
    else if (trafficLights[BOTTOM].isGreen) {
        direction = BOTTOM;
        newVehicle.rect.x = (GetRandomValue(0, 1) == 0) ? 350 : 380;
        newVehicle.rect.y = GetScreenHeight();
        newVehicle.speed = -5;
    }

    // If a valid direction is chosen, set the vehicle's direction and color
    if (direction != -1) {
        newVehicle.direction = static_cast<Direction>(direction);
        newVehicle.color = getRandomColor();
        vehicles.push_back(newVehicle);
    }
}

// Function to update vehicles
void updateVehicles() {
    for (auto& vehicle : vehicles) {
        if (vehicle.active) {
            bool shouldStop = false;

            // Stop vehicles that are not in the direction of the current green light
            if (vehicle.direction == LEFT && currentLight != 0) shouldStop = true; // Stop if not left light
            if (vehicle.direction == RIGHT && currentLight != 1) shouldStop = true; // Stop if not right light
            if (vehicle.direction == TOP && currentLight != 2) shouldStop = true; // Stop if not top light
            if (vehicle.direction == BOTTOM && currentLight != 3) shouldStop = true; // Stop if not bottom light

            // Only allow movement if the light is green and the vehicle is on the correct side
            if (shouldStop && !trafficLights[currentLight].isGreen) {
                continue; // Skip moving the vehicle if the light is not green
            }

            // Move the vehicle based on its direction
            if (vehicle.direction == LEFT || vehicle.direction == RIGHT) {
                vehicle.rect.x += vehicle.speed;
            } else {
                vehicle.rect.y += vehicle.speed;
            }

            // Deactivate the vehicle if it goes off-screen
            if (vehicle.rect.x > GetScreenWidth() || vehicle.rect.x < -vehicle.rect.width ||
                vehicle.rect.y > GetScreenHeight() || vehicle.rect.y < -vehicle.rect.height) {
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

// Function to get a random color for the vehicles
Color getRandomColor() {
    int colorChoice = GetRandomValue(0, 2);
    switch (colorChoice) {
        case 0: return RED;
        case 1: return BLUE;
        case 2: return YELLOW;
        default: return WHITE;
    }
}

// Function to draw traffic light indicators
void drawTrafficLightIndicator() {
    for (int i = 0; i < 4; i++) {
        DrawRectangle(trafficLights[i].rect.x, trafficLights[i].rect.y, trafficLights[i].rect.width, trafficLights[i].rect.height, DARKGRAY);
        DrawCircle(trafficLights[i].rect.x + trafficLights[i].rect.width / 2, trafficLights[i].rect.y + 20, 15, trafficLights[i].isGreen ? DARKGRAY : RED);
        DrawCircle(trafficLights[i].rect.x + trafficLights[i].rect.width / 2, trafficLights[i].rect.y + 50, 15, trafficLights[i].isGreen ? GREEN : DARKGRAY);
    }
}

// Function to update traffic light state
void updateTrafficLight() {
    static int frameCounter = 0;
    frameCounter++;

    // Switch lights every 180 frames (for example)
    if (frameCounter % 180 == 0) {
        trafficLights[currentLight].isGreen = false;
        currentLight = (currentLight + 1) % 4; // Rotate through traffic lights
        trafficLights[currentLight].isGreen = true;
        frameCounter = 0;
    }
}
