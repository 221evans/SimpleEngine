//
// Created by Jason Evans on 21/03/2025.
//

#include "Game.hpp"
#include <iostream>

Game::Game()
{
    isPlayerTurn = true;
    isEnemyTurn = false;
    enemyTurnInitialized = false;
    playerTurnInitialized = false;
}

Game::~Game()
{
}

void Game::Init()
{
    InitWindow(800, 600, "Turn based RPG");
    player.Init();
    enemy.Init();
    std::cout << "Game Initialized. Players Turn First." << std::endl;
}

void Game::Update(float deltaTime)
{
    deltaTime = GetFrameTime();
    player.Update(deltaTime);
    enemy.Update(deltaTime);
    DrawUI();
    if (isPlayerTurn)
    {
        HandlePlayerTurn();
    }
    else if (isEnemyTurn)
    {
        HandleEnemyTurn();
    }
}

void Game::HandlePlayerTurn()
{
    if (!playerTurnInitialized)
    {
        player.StartTurn();
        playerTurnInitialized = true;
    }

    if (IsKeyPressed(KEY_ONE))
    {
        player.TriggerAttack();
    }

    if (player.isAttackComplete())
    {
        std::cout << "Player Action complete. Switching to enemy turn" << std::endl;
        SwitchToEnemyTurn();
    }
}

void Game::HandleEnemyTurn()
{
    if (!enemyTurnInitialized)
    {
        enemy.StartTurn();
        enemyTurnInitialized = true;
    }

    std::cout << "Enemy state: isAttacking=" << enemy.isAttacking
              << ", attackTriggered=" << enemy.attackTriggered
              << ", actionCompletedThisTurn=" << enemy.actionCompletedThisTurn << std::endl;


    if (!enemy.isAttacking && !enemy.attackTriggered && !enemy.actionCompletedThisTurn)
    {
        enemy.EnemyAttack();
    }

    if (enemy.IsAttackComplete())
    {
        std::cout << "Enemy action complete. Switching to player turn." << std::endl;
        SwitchToPlayerTurn();
    }
}

void Game::SwitchToPlayerTurn()
{
    isPlayerTurn = true;
    isEnemyTurn = false;
    playerTurnInitialized = false;
    enemy.ResetAttackState();
}

void Game::SwitchToEnemyTurn()
{
    isPlayerTurn = false;
    isEnemyTurn = true;
    enemyTurnInitialized = false;
    player.ResetAttackState();
}

void Game::DrawUI()
{
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







