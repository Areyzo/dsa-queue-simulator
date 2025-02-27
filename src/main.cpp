#include "traffic_simulation.hpp"
#include <stdio.h>

// Forward declaration for the drawTrafficLightIndicator function
void drawTrafficLightIndicator();

void simulateTraffic();

int main() {
    simulateTraffic();
    return 0;
}

void simulateTraffic() {
    InitWindow(800, 800, "Traffic Simulation");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("Images/img.png");
    if (background.id == 0) {
        printf("Failed to load texture img.png\n");
        return;
    } else {
        printf("Texture loaded successfully\n");
    }

    static int frameCounter = 0;

    while (!WindowShouldClose()) {
        frameCounter++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the background
        DrawTexturePro(background, 
            (Rectangle){0, 0, (float)background.width, (float)background.height}, 
            (Rectangle){0, 0, 800, 800}, 
            (Vector2){0, 0}, 0.0f, WHITE);

        DrawText("Traffic Simulation", 10, 10, 20, WHITE);

        // Create a vehicle every 60 frames
        if (frameCounter % 60 == 0) {
            createVehicle();
        }

        // Update and draw vehicles
        updateVehicles();
        for (auto& vehicle : vehicles) {
            if (vehicle.active) {
                // Draw the vehicle with its assigned color
                DrawRectangleV({vehicle.rect.x, vehicle.rect.y}, {vehicle.rect.width, vehicle.rect.height}, vehicle.color);
            }
        }

        // Update traffic light state
        updateTrafficLight();

        // Draw the traffic light indicator
        drawTrafficLightIndicator();

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
}
