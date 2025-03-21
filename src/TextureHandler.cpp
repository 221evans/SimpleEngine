//
// Created by Jason Evans on 21/03/2025.
//

#include "TextureHandler.hpp"

void TextureHandler::LoadPlayerTextures()
{
    playerIdle = LoadTexture("Assets/Player/playerIdle.png");
    playerRun = LoadTexture("Assets/Player/playerRun.png");
    playerJump = LoadTexture("Assets/Player/playerJump.png");
    playerAttack = LoadTexture("Assets/Player/playerAttack.png");
    playerDead = LoadTexture("Assets/Player/playerDead.png");
}

void TextureHandler::LoadBlackBoarTextures()
{
    blackBoarIdle = LoadTexture("../Assets/Enemy/blackBoarIdle.png");
    blackBoarRun = LoadTexture("../Assets/Enemy/blackBoarRun.png");
    blackBoarAttack = LoadTexture("../Assets/Enemy/blackBoarAttack.png");
    blackBoarDead = LoadTexture("../Assets/Enemy/blackBoarDead.png");
}

void TextureHandler::UnloadTextures() const
{
    // Unload player
    UnloadTexture(playerIdle);
    UnloadTexture(playerRun);
    UnloadTexture(playerJump);
    UnloadTexture(playerAttack);
    UnloadTexture(playerDead);
    // Unload black boar
    UnloadTexture(blackBoarIdle);
    UnloadTexture(blackBoarRun);
    UnloadTexture(blackBoarAttack);
    UnloadTexture(blackBoarDead);
}
