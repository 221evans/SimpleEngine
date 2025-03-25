// src/Game.cpp
#include "Game.hpp"
#include "Entity/PlayerEntity.hpp"
#include "Entity/EnemyEntity.hpp"
#include "raylib.h"
#include <iostream>

Game::Game() :
    isPlayerTurn(true),
    isEnemyTurn(false),
    playerTurnInitialized(false),
    enemyTurnInitialized(false) {
}

Game::~Game() {
    entities.clear();
}

void Game::Init() {
    InitWindow(800, 600, "Turn Based RPG");
    // Load background Image
    textureHandler.LoadBackgroundTexture();

    // Create player entity
    player = std::make_shared<PlayerEntity>();
    AddEntity(player);

    // Create enemy entity
    enemy = std::make_shared<EnemyEntity>();
    AddEntity(enemy);

    // Initialize all entities
    for (auto& entity : entities) {
        entity->Init();
    }
    std::cout << "Game Initialized. Player's Turn First." << std::endl;
}

void Game::Draw()
{
    Rectangle sourceRec = {
    0.0,0.0f,
        (float)textureHandler.background.width,(float)textureHandler.background.height,
    };

    Rectangle destRec = {
    0.0,0.0f,
    (float)GetScreenWidth(),(float)GetScreenHeight(),

    };

    Vector2 origin = {0.0f,0.0f};

    DrawTexturePro(textureHandler.background,sourceRec,destRec,origin,0.0f,WHITE);

    // Draw UI
    DrawUI();

    for (auto& entity : entities) {
        entity->Draw();
    }
}



void Game::Update(float deltaTime) {

    Draw();

    // Update all entities
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }

    // Handle turn-based mechanics
    if (isPlayerTurn) {
        HandlePlayerTurn();
    }
    else if (isEnemyTurn) {
        HandleEnemyTurn();
    }
}

void Game::HandlePlayerTurn() {
    if (!playerTurnInitialized) {
        player->StartTurn();
        playerTurnInitialized = true;
    }

    // Check for player actions
    if (IsKeyPressed(KEY_ONE)) {
        player->TriggerAttack();
    }

    // Check if player has completed their action
    if (player->IsAttackComplete()) {
        std::cout << "Player action complete. Switching to enemy turn." << std::endl;
        SwitchToEnemyTurn();
    }
}

void Game::HandleEnemyTurn() {
    if (!enemyTurnInitialized) {
        enemy->StartTurn();
        enemyTurnInitialized = true;
    }

    // Enemy AI logic - simple for now, just attack
    if (!enemy->IsAttackComplete()) {
        enemy->EnemyAttack();
    }

    // Check if enemy has completed their action
    if (enemy->IsAttackComplete()) {
        std::cout << "Enemy action complete. Switching to player turn." << std::endl;
        SwitchToPlayerTurn();
    }
}

void Game::SwitchToPlayerTurn() {
    isPlayerTurn = true;
    isEnemyTurn = false;
    playerTurnInitialized = false;
    enemy->ResetAttackState();
}

void Game::SwitchToEnemyTurn() {
    isPlayerTurn = false;
    isEnemyTurn = true;
    enemyTurnInitialized = false;
    player->ResetAttackState();
}

void Game::DrawUI() {
    // Add a turn indicator
    std::string turnText = isPlayerTurn ? "PLAYER TURN" : "ENEMY TURN";
    DrawText(turnText.c_str(), 300, 370, 20, DARKGRAY);

    // Draw action buttons
    DrawText("1: ATTACK", 100, 480, 20, BLACK);
    DrawText("2: DEFEND", 250, 480, 20, BLACK);
    DrawText("3: ITEM", 400, 480, 20, BLACK);
    DrawText("4: RUN", 550, 480, 20, BLACK);
}

void Game::AddEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}





