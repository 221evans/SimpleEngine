// src/EnemyEntity.cpp
#include "EnemyEntity.hpp"
#include "SpriteComponent.hpp"
#include "CombatComponent.hpp"
#include <iostream>

EnemyEntity::EnemyEntity() :
    attackTimer(0.0f),
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

void EnemyEntity::Init() {
    // Create and initialize components
    textureHandler.LoadBlackBoarTextures();

    // Create sprite component
    spriteComponent = std::make_shared<SpriteComponent>();

    // Set up animations
    spriteComponent->SetTexture("idle", textureHandler.blackBoarIdle, 4, 96, 64);
    spriteComponent->SetTexture("run", textureHandler.blackBoarRun, 6, 96, 64);
    spriteComponent->SetTexture("attack", textureHandler.blackBoarAttack, 8, 96, 64);
    spriteComponent->SetTexture("dead", textureHandler.blackBoarDead, 4, 96, 64);

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
    // Update collision rectangle
    collisionRec.x = position.x;
    collisionRec.y = position.y;
    collisionRec.width = spriteComponent->GetWidth();
    collisionRec.height = spriteComponent->GetHeight();

    // Update all components
    Entity::Update(deltaTime);
}

void EnemyEntity::Draw() {
    // Draw is handled by the components
    Entity::Draw();
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