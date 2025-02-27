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

    int direction = GetRandomValue(0, 3); // 0 = left, 1 = right, 2 = top, 3 = bottom
    newVehicle.direction = static_cast<Direction>(direction);

    // Set the spawn position based on the direction (two lanes per side)
    if (direction == LEFT && trafficLights[0].isGreen) { // Left (two fixed y positions for lanes)
        newVehicle.rect.x = -newVehicle.rect.width;
        newVehicle.rect.y = (GetRandomValue(0, 1) == 0) ? 350 : 380;
    } else if (direction == RIGHT && trafficLights[1].isGreen) { // Right (two fixed y positions for lanes)
        newVehicle.rect.x = GetScreenWidth();
        newVehicle.rect.y = (GetRandomValue(0, 1) == 0) ? 400 : 430;
        newVehicle.speed = -5;
    } else if (direction == TOP && trafficLights[2].isGreen) { // Top (two fixed x positions for lanes)
        newVehicle.rect.x = (GetRandomValue(0, 1) == 0) ? 400 : 430;
        newVehicle.rect.y = -newVehicle.rect.height;
    } else if (direction == BOTTOM && trafficLights[3].isGreen) { // Bottom (two fixed x positions for lanes)
        newVehicle.rect.x = (GetRandomValue(0, 1) == 0) ? 350 : 380;
        newVehicle.rect.y = GetScreenHeight();
        newVehicle.speed = -5;
    } else {
        // If there is no green light, don't spawn the vehicle
        return;
    }

    newVehicle.color = getRandomColor();
    vehicles.push_back(newVehicle);
}

// Function to update vehicles
void updateVehicles() {
    // Calculate 40% of screen width/height
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());
    float horizontalThreshold = screenWidth * 0.4f;
    float verticalThreshold = screenHeight * 0.4f;

    for (auto& vehicle : vehicles) {
        if (vehicle.active) {
            bool shouldStop = false;

            // Stop vehicles that are not in the direction of the current green light and haven't passed the 40% threshold
            if (vehicle.direction == LEFT && !trafficLights[0].isGreen && vehicle.rect.x < horizontalThreshold) shouldStop = true;
            if (vehicle.direction == RIGHT && !trafficLights[1].isGreen && vehicle.rect.x > screenWidth - horizontalThreshold) shouldStop = true;
            if (vehicle.direction == TOP && !trafficLights[2].isGreen && vehicle.rect.y < verticalThreshold) shouldStop = true;
            if (vehicle.direction == BOTTOM && !trafficLights[3].isGreen && vehicle.rect.y > screenHeight - verticalThreshold) shouldStop = true;

            // Only allow movement if the light is green and the vehicle is on the correct side
            if (shouldStop) {
                continue; // Skip moving the vehicle if the light is not green and it's before the 40% threshold
            }

            // Move the vehicle based on its direction
            if (vehicle.direction == LEFT || vehicle.direction == RIGHT) {
                vehicle.rect.x += vehicle.speed;
            } else {
                vehicle.rect.y += vehicle.speed;
            }

            // Deactivate the vehicle if it goes off-screen
            if (vehicle.rect.x > screenWidth || vehicle.rect.x < -vehicle.rect.width ||
                vehicle.rect.y > screenHeight || vehicle.rect.y < -vehicle.rect.height) {
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

// Function to draw traffic light indicators with labels
void drawTrafficLightIndicator() {
    const int labelOffsetX = 60; // X offset for label text (to the right of the traffic light)
    const int labelOffsetY = 20; // Y offset for label text (slightly below the traffic light)

    for (int i = 0; i < 4; i++) {
        // Draw traffic light rectangle
        DrawRectangle(trafficLights[i].rect.x, trafficLights[i].rect.y, trafficLights[i].rect.width, trafficLights[i].rect.height, DARKGRAY);

        // Draw the top light (red and green circles)
        DrawCircle(trafficLights[i].rect.x + trafficLights[i].rect.width / 2, trafficLights[i].rect.y + 20, 15, trafficLights[i].isGreen ? DARKGRAY : RED);
        DrawCircle(trafficLights[i].rect.x + trafficLights[i].rect.width / 2, trafficLights[i].rect.y + 50, 15, trafficLights[i].isGreen ? GREEN : DARKGRAY);

        // Label the traffic light (Top, Left, Right, Bottom)
        const char* label = "";
        switch (i) {
            case 0: label = "Left"; break;
            case 1: label = "Right"; break;
            case 2: label = "Top"; break;
            case 3: label = "Bottom"; break;
        }

        // Draw the label next to the traffic light
        DrawText(label, trafficLights[i].rect.x + labelOffsetX, trafficLights[i].rect.y + labelOffsetY, 20, WHITE);
    }
}

// Function to update traffic light state
void updateTrafficLight() {
    static int frameCounter = 0;
    frameCounter++;

    // Switch lights every 60 frames (to triple the spawn rate, make the interval shorter)
    if (frameCounter % 100 == 0) {
        trafficLights[currentLight].isGreen = false;
        currentLight = (currentLight + 1) % 4; // Rotate through traffic lights
        trafficLights[currentLight].isGreen = true;
        frameCounter = 0;
    }
}
