// src/Game.cpp
#include "Game.hpp"
#include "Entity/PlayerEntity.hpp"
#include "Entity/EnemyEntity.hpp"
#include "raylib.h"
#include <iostream>

#include "Entity/SpriteComponent.hpp"

Game::Game() :
    isPlayerTurn(true),
    isEnemyTurn(false),
    playerTurnInitialized(false),
    enemyTurnInitialized(false),
    currentState(GameState::EXPLORATION),
    stateTransitionTimer(0.0f) {

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
        if (entity)
        {
            entity->Draw();
        }
    }
}

void Game::Update(float deltaTime) {

    if (currentState == GameState::TRANSITION_TO_COMBAT)
    {
        stateTransitionTimer += deltaTime;
        if (stateTransitionTimer >= TRANSITION_DURATION) {
            currentState = GameState::COMBAT;
            stateTransitionTimer = 0.0f;
            // Start combat with player's turn
            player->StartTurn();
            playerTurnInitialized = true;
        }
    }
    else if (currentState == GameState::TRANSITION_TO_EXPLORATION) {
        stateTransitionTimer += deltaTime;
        if (stateTransitionTimer >= TRANSITION_DURATION) {
            currentState = GameState::EXPLORATION;
            stateTransitionTimer = 0.0f;
        }
    }
    // Update game based on current state
    switch (currentState) {
    case GameState::EXPLORATION:
        HandleExplorationMode(deltaTime);
        break;

    case GameState::COMBAT:
        HandleCombatMode(deltaTime);
        break;

    case GameState::TRANSITION_TO_COMBAT:
    case GameState::TRANSITION_TO_EXPLORATION:
        // Just update entities during transitions
        for (auto& entity : entities) {
            entity->Update(deltaTime);
        }
        break;
    }

    Draw();
}

void Game::HandleExplorationMode(float deltaTime)
{
    // Update all entities
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }

    if (!enemy) {
        SpawnNewEnemy();
        enemy->SetHealth(100);
        std::cout << "Is Enemy Dead? " << enemy->IsDead() << std::endl;
    }

    CheckCollisions();
}

void Game::CheckCollisions()
{
    if (currentState != GameState::EXPLORATION) return;

    Rectangle playerRect = player->GetCollisionRect();
    Rectangle enemyRect = enemy->GetCollisionRect();

    if (CheckCollisionRecs(playerRect, enemyRect)) {
        TransitionToCombat();
    }
}

void Game::TransitionToCombat()
{
    currentState = GameState::TRANSITION_TO_COMBAT;
    stateTransitionTimer = 0.0f;
    isPlayerTurn = true;

    // Update player and enemy states
    player->SetInCombat(true);
    enemy->SetInCombat(true);

    // Position entities appropriately for combat
    player->SetPosition({100.0f, 535.0f});
    enemy->SetPosition({400.0f, 535.0f});

    // Reset animation states
    if (auto playerSprite = player->GetComponent<SpriteComponent>())
    {
        playerSprite->SetAnimation("idle");

        if (playerSprite->playerIsFacingLeft == true)
        {
            playerSprite->FlipHorizontal(false);
            std::cout <<"Flipping player" << std::endl;
        }
    }

    if (auto enemySprite = enemy->GetComponent<SpriteComponent>())
    {
        enemySprite->SetAnimation("idle");
        if (enemySprite->enemyIsFacingLeft == false)
        {
            enemySprite->FlipHorizontal(false);
        }
    }


    std::cout << "Entering combat!" << std::endl;
}

void Game::TransitionToExploration()
{
    currentState = GameState::TRANSITION_TO_EXPLORATION;
    stateTransitionTimer = 0.0f;

    // Reset combat state completely
    isPlayerTurn = true;
    isEnemyTurn = false;
    playerTurnInitialized = false;
    enemyTurnInitialized = false;

    // Checks if player still exists
    if (player)
    {
        player->SetInCombat(false);
        player->ResetAttackState();

        if (auto playerSprite = player->GetComponent<SpriteComponent>())
            playerSprite->SetAnimation("idle");
    }

    // Checks if enemy still exists
    if (enemy)
    {
        // Move enemy away from player to avoid immediately triggering combat again
        Vector2 playerPos = player->GetPosition();
        enemy->SetPosition({playerPos.x + 200.0f, playerPos.y});

        if (auto enemySprite = enemy->GetComponent<SpriteComponent>())
            enemySprite->SetAnimation("idle");
        enemy->SetInCombat(false);
    }



    std::cout << "Returning to exploration!" << std::endl;



}

void Game::HandleCombatMode(float deltaTime) {
    // Check for dead entities first
    CheckEntityHealth();

    // Exit if enemy is dead after health check
    if (!enemy) return;

    // Update all entities
    for (auto& entity : entities) {
        if (entity) { // Add null check
            entity->Update(deltaTime);
        }
    }

    // Handle turn-based mechanics (only if enemy exists)
    if (enemy) {
        if (isPlayerTurn) {
            HandlePlayerTurn();
        }
        else if (isEnemyTurn) {
            HandleEnemyTurn();
        }
    }

    // Check if combat is over (can be enhanced later with victory/defeat conditions)
    if (IsKeyPressed(KEY_FOUR)) {
        TransitionToExploration();
        std::cout << "You ran like a coward" << std::endl;
    }
}


void Game::HandlePlayerTurn() {

    if (!player || !enemy) return;

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
        enemy->SetHealth(enemy->GetHealth() - player->playerDamage);
        std::cout << enemy->GetHealth() << std::endl;
        std::cout << enemy->IsDead() << std::endl;

        if (enemy->IsDead()) {
            CheckEntityHealth();
            isEnemyTurn = false;
            isPlayerTurn = false;
            return; // Exit early if enemy is dead
        }

        SwitchToEnemyTurn();
    }

    if (enemy && enemy->IsDead()) {
        CheckEntityHealth();
        return;
    }
}

void Game::HandleEnemyTurn() {

    if (!enemy || !player) return;

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
    if (currentState == GameState::COMBAT || currentState == GameState::TRANSITION_TO_COMBAT) {
        // Combat UI
        std::string turnText = isPlayerTurn ? "PLAYER TURN" : "ENEMY TURN";
        DrawText(turnText.c_str(), 300, 370, 20, DARKGRAY);

        // Draw action buttons
        DrawText("1: ATTACK", 100, 480, 20, BLACK);
        DrawText("2: DEFEND", 250, 480, 20, BLACK);
        DrawText("3: ITEM", 400, 480, 20, BLACK);
        DrawText("4: RUN", 550, 480, 20, BLACK);
    }
    else if (currentState == GameState::EXPLORATION || currentState == GameState::TRANSITION_TO_EXPLORATION) {
        // Exploration UI - minimal for now
        DrawText("EXPLORATION MODE", 300, 50, 20, DARKGRAY);
        DrawText("Arrow Keys: Move | ESC: Menu", 260, 80, 20, DARKGRAY);
    }

    // Show transition effect if in transition
    if (currentState == GameState::TRANSITION_TO_COMBAT || currentState == GameState::TRANSITION_TO_EXPLORATION) {
        float alpha = (currentState == GameState::TRANSITION_TO_COMBAT)
            ? stateTransitionTimer / TRANSITION_DURATION
            : 1.0f - (stateTransitionTimer / TRANSITION_DURATION);

        Color transColor = {0, 0, 0, (unsigned char)(alpha * 180)};
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), transColor);
    }
}

void Game::CheckEntityHealth()
{
    if (enemy && enemy->IsDead())
    {
        std::cout << "Enemy is dead" << std::endl;

        //Reset turn flags
        isPlayerTurn = true;
        isEnemyTurn = false;
        playerTurnInitialized = false;
        enemyTurnInitialized = false;

        // Remove enemy from entities list
        auto it = std::find(entities.begin(), entities.end(), enemy);
        if (it != entities.end()) {
            entities.erase(it);
        }

        enemy = nullptr;

        if (currentState == GameState::COMBAT) {
            TransitionToExploration();
        }
    }
}

void Game::SpawnNewEnemy()
{
    if (!enemy)
    {
        enemy = std::make_shared<EnemyEntity>();
        enemy->Init();

        Vector2 playerPos = player->GetPosition();
        enemy->SetPosition({playerPos.x + 300.0f, playerPos.y});

        AddEntity(enemy);
        std::cout << "New enemy spawned!" << std::endl;

    }
}

void Game::AddEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}





