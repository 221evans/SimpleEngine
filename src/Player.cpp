//
// Created by Jason Evans on 11/03/2025.
//

#include "Player.hpp"
#include <iostream>
#include <raylib.h>

Player::Player()
{
    posX = 100;
    posY = 500;
    width = 64;
    height = 64;
    playerHealth = 100;
    speed = 100;
    rotation = 0;
    attackWasTriggered = false;
    attackAnimationComplete = false;
    currentFrame = 0;


}

Player::~Player()
{

}
void Player::Init()
{
    textureHandler.LoadPlayerTextures();
    position = (Vector2){static_cast<float>(posX), static_cast<float>(posY)};
    collisionRec = (Rectangle){position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}

bool Player::CheckCollision(Rectangle rec1, Rectangle rec2)
{
    return (rec1.x < rec2.x + rec2.width &&
               rec1.x + rec1.width > rec2.x &&
               rec1.y < rec2.y + rec2.height &&
               rec1.y + rec1.height > rec2.y);
}

void Player::Jump(float deltaTime)
{
    float gravity = 500.0f;
    velocity += gravity * deltaTime;
    position.y += velocity * deltaTime;

    float groundY = 535.0f;
    if (position.y >= groundY) {
        position.y = groundY;
        velocity = 0;
        isGrounded = true;
        isJumping = false;
    }
    else {
        isGrounded = false;
    }
    if (IsKeyPressed(KEY_SPACE) && isGrounded) {
        velocity = -300.0f;
        isGrounded = false;
        isJumping = true;
    }
}


void Player::Draw()
{
    collisionRec.x = position.x;
    collisionRec.y = position.y;
    collisionRec.width = width;
    collisionRec.height = height;
    // Draw collision rec around player
    DrawRectangleLines(collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height, RED);

    sourceRec = {0,0,0,0};
    sourceRec.x = currentFrame * frameWidth;
    sourceRec.y = 0;
    sourceRec.width = width;
    sourceRec.height = height;

    origin.x = 0;
    origin.y = 0;

    destRect.width = width;
    destRect.height = height;
    destRect.x = position.x;
    destRect.y = position.y;

    if (isFacingLeft) {
        sourceRec.width = -width;
    }
    else {
        sourceRec.width = width;
    }

    if (isRunning) {
        currentPlayerTexture = textureHandler.playerRun;
    }
    else if (isJumping) {
        currentPlayerTexture = textureHandler.playerJump;
    }
    else if(isAttacking) {
        currentPlayerTexture = textureHandler.playerAttack;
    }
    else if (playerHealth <= 0) {
        currentPlayerTexture = textureHandler.playerDead;
        isDead = true;
    }
    else {
        currentPlayerTexture = textureHandler.playerIdle;
    }

    DrawTexturePro(currentPlayerTexture,sourceRec,destRect,origin,rotation, WHITE);
}


void Player::Update(float deltaTime)
{
    frameTime += deltaTime;

    frameCount = 4;
    frameWidth = 64;
    width = 64;
    height = 64;
    frameDuration = 0.15f;

    if (isRunning)
    {
        frameCount = 8;
        frameWidth = 80;
        width = 80;
        height = 80;
        frameDuration = 0.15f;
    } else if (isJumping)
    {
        frameCount = 15;
        frameWidth = 64;
        width = 64;
        height = 64;
        frameDuration = 0.15f;
    } else if (isAttacking)
    {
        frameCount = 8;
        frameWidth = 96;
        width = 96;
        height = 80;
        frameDuration = 0.30f;
    } else if (isDead)
    {
        frameCount = 4;
        frameWidth = 64;
        width = 64;
        height = 64;
        frameDuration = 0.15f;
    }

    // Update animation frame
    if (frameTime >= frameDuration)
    {
        frameTime = 0;
        currentFrame++;
        if (currentFrame >= frameCount)
        {
            currentFrame = 0;
            // If this was an attack, mark it as complete
            if (isAttacking && attackTriggered)
            {
                attackAnimationComplete = true;
                attackTriggered = false;
                isAttacking = false;
            }
        }
    }

    Draw();
    PlayerAttack();
    Jump(deltaTime);
}

void Player::ResetAttackState()
{
    isAttacking = false;
    attackTriggered = false;
    attackWasTriggered = false;
    std::cout << "Player attack state reset" << std::endl;
}

void Player::PlayerAttack()
{
    if (attackTriggered && !attackAnimationComplete)
    {
        isAttacking = true;
    }
}


void Player::StartTurn()
{
    actionCompletedThisTurn = false;
    std::cout << "Player starting turn" << std::endl;
}

void Player::TriggerAttack()
{
    if (!isAttacking && !attackTriggered)
    {
        attackTriggered = true;
        currentFrame = 0;
        frameTime = 0;
        attackAnimationComplete = false;
        std::cout << "Player attack triggered" << std::endl;
    }
}

bool Player::isAttackComplete()
{
    return actionCompletedThisTurn;
}






