//
// Created by Jason Evans on 21/03/2025.
//

#include "Enemy.hpp"

#include <iostream>


Enemy::Enemy()
{
    posX = 200;
    posY = 535;
    rotation = 0.0f;
    height = 64;
    width = 96;

    isAttacking = false;
    attackTriggered = false;
    actionCompletedThisTurn = false;
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
    textureHandler.LoadBlackBoarTextures();
    position = (Vector2){static_cast<float>(posX), static_cast<float>(posY)};
    collisionRec = (Rectangle){position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}

void Enemy::EnemyAttack()
{
    if (!isAttacking)
    {
        isAttacking = true;
        attackTriggered = true;
        std::cout << "Enemy Attacks" << std::endl;

        attackTimer = 0.0f;
        attackDuration = 1.0f;

    }
}

bool Enemy::IsAttackComplete()
{
    return actionCompletedThisTurn;
}

void Enemy::StartTurn()
{
    actionCompletedThisTurn = false;
    std::cout << "Enemy Turn Started" << std::endl;

}


void Enemy::Draw()
{
    collisionRec.x = position.x;
    collisionRec.y = position.y;
    collisionRec.width = width;
    collisionRec.height = height;

    DrawRectangleLines(collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height, RED);

    sourceRec = {0,0,0,0};
    sourceRec.x = currentFrame * frameWidth;
    sourceRec.y = 0;
    sourceRec.width = width;
    sourceRec.height = height;

    origin.x = 0;
    origin.y = 0;
    destRec.width = width;
    destRec.height = height;
    destRec.x = position.x;
    destRec.y = position.y;
    currentEnemyTexture = textureHandler.blackBoarIdle;

    DrawTexturePro(currentEnemyTexture,sourceRec,destRec,origin,rotation,WHITE);
}

void Enemy::ResetAttackState()
{
    isAttacking = false;
    attackTriggered = false;
}


void Enemy::Update(float deltaTime)
{
    if (isAttacking)
    {
        attackTimer += deltaTime;
        std::cout << "Enemy attack timer: " << attackTimer << " / " << attackDuration << std::endl;

        if (attackTimer >= attackDuration)
        {
            isAttacking = false;
            attackTriggered = false;
            actionCompletedThisTurn = true;
            std::cout << "Enemy attack animation complete" << std::endl;
        }
    }

    Draw();
}
