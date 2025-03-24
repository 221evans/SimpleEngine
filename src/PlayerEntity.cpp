//
// Created by Jason Evans on 24/03/2025.
//

#include "PlayerEntity.hpp"
#include "SpriteComponent.hpp"
#include "CombatComponent.hpp"
#include <iostream>

PlayerEntity::PlayerEntity() :
    velocity(0.0f),
    isJumping(false),
    isGrounded(true) {

    // Set entity type
    entityType = "Player";

    // Set initial position
    position = {100.0f, 500.0f};

    // Set collision rectangle
    collisionRec = {position.x, position.y, 64.0f, 64.0f};

    // Set initial health
    health = 100;
}

PlayerEntity::~PlayerEntity() {
    // Components will be cleaned up by the Entity destructor
}

void PlayerEntity::Init()
{
    // Create and initialize components
    textureHandler.LoadPlayerTextures();
    // Create spriteComponent
    spriteComponent = std::make_shared<SpriteComponent>();

    // Setup animations
    spriteComponent->SetTexture("idle", textureHandler.playerIdle, 4,64);
    spriteComponent->SetTexture("run", textureHandler.playerRun, 8,80);
    spriteComponent->SetTexture("jump", textureHandler.playerJump, 15,64);
    spriteComponent->SetTexture("attack", textureHandler.playerAttack,8,96);
    spriteComponent->SetTexture("dead", textureHandler.playerDead, 4,64);

    // Initial animation
    spriteComponent->SetAnimation("idle");

    // Add sprite component to entity
    AddComponent(spriteComponent);

    //Create combat component
    combatComponent = std::make_shared<CombatComponent>();
    combatComponent->SetAttackAnimation("attack");
    combatComponent->SetIdleAnimation("idle");
    combatComponent->SetAttackPower(20);

    AddComponent(combatComponent);


    Entity::Init();

}

void PlayerEntity::Update(float deltaTime)
{
    // Update jump mechanics
    Jump(deltaTime);


    // Update collision rec
    collisionRec.x = position.x;
    collisionRec.y = position.y;
    collisionRec.width = spriteComponent->GetWidth();
    collisionRec.height = spriteComponent->GetHeight();

    Entity::Update(deltaTime);
}

void PlayerEntity::Draw()
{
    Entity::Draw();
}

void PlayerEntity::Jump(float deltaTime) {
    float gravity = 500.0f;
    velocity += gravity * deltaTime;
    position.y += velocity * deltaTime;

    float groundY = 500.0f;
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

        // Change animation to jump
        spriteComponent->SetAnimation("jump");
    }

    // If we were jumping but are now on the ground, go back to idle
    if (!isJumping && isGrounded && !combatComponent->IsAttacking()) {
        spriteComponent->SetAnimation("idle");
    }
}

void PlayerEntity::TriggerAttack() {
    combatComponent->Attack();
}

bool PlayerEntity::IsAttackComplete() {
    return actionCompletedThisTurn;
}

void PlayerEntity::ResetAttackState() {
    combatComponent->ResetState();
    Entity::ResetActionState();
}

