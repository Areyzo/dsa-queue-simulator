#include "raylib.h"

int main(void)
{
    // Initialize the window with a temporary size
    InitWindow(1600, 1200, "dsa-queue-simulator");

    // Get the monitor's full resolution
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);
-
    // Switch to fullscreen
    ToggleFullscreen();

    // Define a dark green color
    const Color darkGreen = {20, 160, 133, 255};

    while (!WindowShouldClose()) // Main loop
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        DrawText("assignment 1",0,0, 20, WHITE);
        EndDrawing();
    }

    CloseWindow(); // Cleanup
    return 0;
}
