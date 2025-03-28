// src/EnemyEntity.cpp
#include "EnemyEntity.hpp"
#include "SpriteComponent.hpp"
#include "CombatComponent.hpp"
#include <iostream>

EnemyEntity::EnemyEntity() :
    attackTimer(0.0f),
    moveSpeed(150.0f),
    movementTimer(0.0f),
    movementDuration(2.0f),
    moveDirection(0.0f),
    directionChangeTimer(0.0f),
    directionChangeDuration(3.0f),
    attackDuration(1.0f) {

    // Set entity type
    entityType = "Enemy";

    // Set initial position
    position = {400.0f, 535.0f};

    // Set collision rectangle
    collisionRec = {position.x, position.y, 96.0f, 64.0f};

    // Set initial health
    health = 100;
}

EnemyEntity::~EnemyEntity() {
    // Components will be cleaned up by the Entity destructor
}

void EnemyEntity::Wander(float deltaTime)
{

    if (inCombat || IsDead() || !spriteComponent) return;

    if (inCombat) return; // Don't wander in combat

    // Update timers
    directionChangeTimer += deltaTime;

    // Change direction periodically
    if (directionChangeTimer >= directionChangeDuration) {
        directionChangeTimer = 0.0f;
        // Random direction: -1 (left), 0 (idle), or 1 (right)
        moveDirection = GetRandomValue(-1, 1);

        // Set animation based on movement
        if (spriteComponent) {
            if (moveDirection == 0) {
                spriteComponent->SetAnimation("idle");
            } else {
                spriteComponent->SetAnimation("run");

                // If sprites start facing LEFT:
                // - When moving left (negative direction), DON'T flip (false)
                // - When moving right (positive direction), DO flip (true)
                bool shouldFlip = (moveDirection > 0);
                spriteComponent->FlipHorizontal(shouldFlip);
            }
        }


    }

    // Move in the current direction
    if (moveDirection != 0) {
        position.x += moveDirection * moveSpeed * deltaTime;

        // Keep enemy within screen bounds (simple boundary check)
        if (position.x < 50) {
            position.x = 50;
            moveDirection = 1; // Reverse direction if hitting left edge



            if (spriteComponent) {
                // When bouncing off left wall to go right, FLIP the sprite
                spriteComponent->FlipHorizontal(true);
                spriteComponent->SetAnimation("run");
            }
        } else if (position.x > 700) {
            position.x = 700;
            moveDirection = -1; // Reverse direction if hitting right edge
            spriteComponent->enemyIsFacingLeft = true;
            if (spriteComponent) {
                // When bouncing off right wall to go left, DON'T flip
                spriteComponent->FlipHorizontal(false);
                spriteComponent->SetAnimation("run");
            }
        }
    }

    if (moveDirection == -1)
    {
        spriteComponent->enemyIsFacingLeft = true;
        std::cout << spriteComponent->enemyIsFacingLeft << " " <<"Enemy is facing left"<< std::endl;
    } else if (moveDirection == 1)
    {
        spriteComponent->enemyIsFacingLeft = false;
        std::cout << spriteComponent->enemyIsFacingLeft << " " << "Enemy is facing right"<< std::endl;
    }


}

void EnemyEntity::Init() {

    // Create and initialize components
    textureHandler.LoadBlackBoarTextures();

    // Create sprite component
    spriteComponent = std::make_shared<SpriteComponent>();

    // Set up animations
    spriteComponent->SetTexture("idle", textureHandler.blackBoarIdle, 4, 96, 64);
    spriteComponent->SetTexture("run", textureHandler.blackBoarRun, 6, 80, 64);
    spriteComponent->SetTexture("attack", textureHandler.blackBoarAttack, 8, 160, 112);
    spriteComponent->SetTexture("dead", textureHandler.blackBoarDead, 8, 144, 96);

    // Initial animation
    spriteComponent->SetAnimation("idle");

    // Add sprite component to entity
    AddComponent(spriteComponent);

    // Create combat component
    combatComponent = std::make_shared<CombatComponent>();
    combatComponent->SetAttackAnimation("attack");
    combatComponent->SetIdleAnimation("idle");
    combatComponent->SetAttackPower(15);
    combatComponent->SetAttackDuration(1.0f);

    // Add combat component to entity
    AddComponent(combatComponent);

    // Initialize all components

        Entity::Init();
}

void EnemyEntity::Update(float deltaTime) {


    if (!inCombat)
    {
        Wander(deltaTime);
    }


    // Update collision rectangle
    collisionRec.x = position.x;
    collisionRec.y = position.y;

    // Only update width/height if spriteComponent exists
    if (spriteComponent) {
        collisionRec.width = spriteComponent->GetWidth();
        collisionRec.height = spriteComponent->GetHeight();
    }

    // Update all components
    Entity::Update(deltaTime);
}

void EnemyEntity::Draw() {
    if (!IsDead())
    {
        Entity::Draw();
    }

}

void EnemyEntity::EnemyAttack() {
    if (combatComponent) {
        combatComponent->Attack();
    }
}

bool EnemyEntity::IsAttackComplete() const {
    return actionCompletedThisTurn;
}

void EnemyEntity::ResetAttackState() {
    if (combatComponent) {
        combatComponent->ResetState();
    }
    Entity::ResetActionState();
}