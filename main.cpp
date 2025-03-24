
#include "raylib.h"
#include <iostream>
#include <filesystem>

#include "src/Game.hpp"

int main()
{
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::filesystem::current_path("..");

    // Verify the change
    std::cout << "New working directory: " << std::filesystem::current_path() << std::endl;

    // Create game instance
    Game game;
    game.Init();

    // Main game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        game.Update(deltaTime);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}