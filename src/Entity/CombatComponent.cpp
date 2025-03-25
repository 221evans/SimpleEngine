// src/CombatComponent.cpp
#include "CombatComponent.hpp"
#include "Entity.hpp"
#include "SpriteComponent.hpp"
#include <iostream>

CombatComponent::CombatComponent() :
    attackPower(10),
    isAttacking(false),
    attackTriggered(false),
    attackAnimationComplete(false),
    attackTimer(0.0f),
    attackDuration(1.0f) {

    componentType = "Combat";
}

CombatComponent::~CombatComponent() {
    // Nothing to destroy
}

void CombatComponent::Init(Entity* owner) {
    // Get reference to the sprite component
    spriteComponent = owner->GetComponent<SpriteComponent>();

    if (!spriteComponent) {
        std::cout << "Combat component requires a sprite component!" << std::endl;
    }
}

void CombatComponent::Update(Entity* owner, float deltaTime) {
    if (!spriteComponent) return;

    if (isAttacking) {
        attackTimer += deltaTime;

        // Check if animation is complete
        if (spriteComponent->IsAnimationComplete() || attackTimer >= attackDuration) {
            isAttacking = false;
            attackAnimationComplete = true;

            // Switch back to idle animation
            spriteComponent->SetAnimation(idleAnimation);

            // Mark the owner's action as complete for this turn
            owner->actionCompletedThisTurn = true;

            std::cout << owner->GetType() << " attack complete" << std::endl;
        }
    }
}

void CombatComponent::Draw(Entity* owner) {
    // Drawing is handled by the sprite component
}

void CombatComponent::Attack() {
    if (!spriteComponent) return;

    if (!isAttacking && !attackTriggered) {
        isAttacking = true;
        attackTriggered = true;
        attackAnimationComplete = false;
        attackTimer = 0.0f;

        // Switch to attack animation
        spriteComponent->SetAnimation(attackAnimation);

        std::cout << "Attack started!" << std::endl;
    }
}

void CombatComponent::Defend() {
    // Implementation for defend action
    std::cout << "Defend action triggered" << std::endl;
}

void CombatComponent::UseItem() {
    // Implementation for using an item
    std::cout << "Use item action triggered" << std::endl;
}

void CombatComponent::ResetState() {
    isAttacking = false;
    attackTriggered = false;
    attackAnimationComplete = false;
}
