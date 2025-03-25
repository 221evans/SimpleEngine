// src/CombatComponent.hpp
#ifndef COMBAT_COMPONENT_HPP
#define COMBAT_COMPONENT_HPP

#include "Component.hpp"
#include <functional>
#include <string>

class SpriteComponent;

class CombatComponent : public Component {
public:
    CombatComponent();
    ~CombatComponent() override;

    void Init(Entity* owner) override;
    void Update(Entity* owner, float deltaTime) override;
    void Draw(Entity* owner) override;

    // Combat actions
    void Attack();
    void Defend();
    void UseItem();

    // State checks
    bool IsAttacking() const { return isAttacking; }
    bool IsAttackComplete() const { return attackAnimationComplete; }

    // Setters
    void SetAttackPower(int power) { attackPower = power; }
    void SetAttackDuration(float duration) { attackDuration = duration; }
    void SetAttackAnimation(const std::string& animName) { attackAnimation = animName; }
    void SetIdleAnimation(const std::string& animName) { idleAnimation = animName; }

    // Reset state for new turn
    void ResetState();

private:
    // Combat properties
    int attackPower;

    // Animation properties
    std::string attackAnimation;
    std::string idleAnimation;

    // State tracking
    bool isAttacking;
    bool attackTriggered;
    bool attackAnimationComplete;
    float attackTimer;
    float attackDuration;

    // References to other components
    std::shared_ptr<SpriteComponent> spriteComponent;
};

#endif // COMBAT_COMPONENT_HPP