//
// Created by Jason Evans on 24/03/2025.
//

#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "Entity.hpp"
#include "../TextureHandler.hpp"

class SpriteComponent;
class CombatComponent;


class PlayerEntity : public Entity {
public:
    PlayerEntity();
    ~PlayerEntity() override;

    void Init() override;
    void Update(float deltaTime) override;
    void Draw() override;

    //Player specific meth
    void TriggerAttack();
    bool IsAttackComplete();
    void ResetAttackState();
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    bool IsInCombat() const { return inCombat; }
    void SetInCombat(bool combat) { inCombat = combat; }

private:
    // Player specific properties
    float velocity;
    bool isJumping;
    bool isGrounded;
    bool inCombat;
    float moveSpeed;


    // Reference to components for easy access
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<CombatComponent> combatComponent;

    TextureHandler textureHandler;
};



#endif //PLAYERENTITY_HPP
