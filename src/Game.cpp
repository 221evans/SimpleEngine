// src/Game.cpp
#include "Game.hpp"
#include "PlayerEntity.hpp"
#include "EnemyEntity.hpp"
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
    InitWindow(800, 600, "Turn Based RPG - Entity System");

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

void Game::Update(float deltaTime) {
    // Update all entities
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }


    for (auto& entity : entities) {
        entity->Draw();
    }

    // Draw UI
    DrawUI();

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
    DrawRectangle(50, 350, 700, 100, BLACK);

    // Add a turn indicator
    std::string turnText = isPlayerTurn ? "PLAYER TURN" : "ENEMY TURN";
    DrawText(turnText.c_str(), 350, 370, 20, YELLOW);

    // Draw action buttons
    DrawText("1: ATTACK", 100, 480, 20, WHITE);
    DrawText("2: DEFEND", 250, 480, 20, WHITE);
    DrawText("3: ITEM", 400, 480, 20, WHITE);
    DrawText("4: RUN", 550, 480, 20, WHITE);
}

void Game::AddEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}





