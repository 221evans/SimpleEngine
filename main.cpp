#include "src/Player.hpp"
#include "raylib.h"
#include "src/TextureHandler.hpp"
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::filesystem::current_path("..");

    // Verify the change
    std::cout << "New working directory: " << std::filesystem::current_path() << std::endl;


    int windowWidth = 800;
    int windowHeight = 600;
    Player player;
    TextureHandler textureHandler;
    InitWindow(windowWidth, windowHeight, "Raylib [core] example - basic window");
    SetTargetFPS(60);
    player.Init();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.Draw();
        player.Update(deltaTime);
        EndDrawing();
    }

    CloseWindow();
    textureHandler.UnloadTextures();
}
