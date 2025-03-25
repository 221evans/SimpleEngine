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

    //Player specific methods
    void Jump(float deltaTime);
    void TriggerAttack();
    bool IsAttackComplete();
    void ResetAttackState();

private:
    // Player specific properties
    float velocity;
    bool isJumping;
    bool isGrounded;

    // Reference to components for easy access
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<CombatComponent> combatComponent;

    TextureHandler textureHandler;
};



#endif //PLAYERENTITY_HPP
