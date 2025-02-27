#include "raylib.h"
#include<stdio.h>

int main(void)
{
    // Initialize the window with a temporary size
    InitWindow(800, 800, "dsa-queue-simulator");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("Images/img.png");
    if (background.id == 0) {
        printf("Failed to load texture img.jpg\n");
        return 1;  // Exit if the texture fails
    }
    else {
        printf("Texture loaded successfully\n");
    }
    
    // Switch to fullscreen
    //ToggleFullscreen();

    while (!WindowShouldClose()) // Main loop
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

         DrawTexturePro(background, 
            (Rectangle){0, 0, background.width, background.height}, 
            (Rectangle){0, 0, 800, 800}, 
            (Vector2){0, 0}, 0.0f, WHITE);

        DrawText("assignment 1",0,0, 20, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow(); // Cleanup
    return 0;
}
