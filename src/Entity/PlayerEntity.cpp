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
    moveSpeed(200.0f),
    inCombat(false),
    isGrounded(true) {

    // Set entity type
    entityType = "Player";

    // Set initial position
    position = {100.0f, 535.0f};

    // Set collision rectangle
    collisionRec = {position.x, position.y, 64.0f, 64.0f};

    // Set initial health
    health = 100;

    playerDamage = 100;
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
    spriteComponent->SetTexture("idle", textureHandler.playerIdle, 4,64, 64);
    spriteComponent->SetTexture("run", textureHandler.playerRun, 8,80, 64);
    spriteComponent->SetTexture("jump", textureHandler.playerJump, 15,64, 80);
    spriteComponent->SetTexture("attack", textureHandler.playerAttack,8,96, 80);
    spriteComponent->SetTexture("dead", textureHandler.playerDead, 4,64, 64);

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
    if (!inCombat)
    {
        bool isMoving = false;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            MoveLeft(deltaTime);
            isMoving = true;
            spriteComponent->playerIsFacingLeft = true;

        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            MoveRight(deltaTime);
            isMoving = true;
            spriteComponent->playerIsFacingLeft = false;

        }

        if (!isMoving && !isJumping && spriteComponent)
        {
            spriteComponent->SetAnimation("idle");
        }

    }

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

void PlayerEntity::MoveLeft(float deltaTime)
{
    if (inCombat) return;

    position.x -= moveSpeed * deltaTime;

    if (spriteComponent && !isJumping)
    {
        spriteComponent->SetAnimation("run");
        spriteComponent->FlipHorizontal(true);
    }
}


void PlayerEntity::MoveRight(float deltaTime)
{
    if (inCombat) return;
    position.x += moveSpeed * deltaTime;

    if (spriteComponent && !isJumping)
    {
        spriteComponent->SetAnimation("run");
        spriteComponent->FlipHorizontal(false);
    }
}
