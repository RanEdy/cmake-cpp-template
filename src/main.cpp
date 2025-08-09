#include "raylib/raylib.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;


void UpdateDrawFrame(void)
{
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}


int main()
{
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
    
    CloseWindow();

    return 0;
}
