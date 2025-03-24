//
// Created by Jason Evans on 24/03/2025.
//

#ifndef ENEMYENTITY_HPP
#define ENEMYENTITY_HPP

#include "Entity.hpp"
#include "TextureHandler.hpp"

class SpriteComponent;
class CombatComponent;


class EnemyEntity : public Entity {
public:
    EnemyEntity();
    ~EnemyEntity() override;

    void Init() override;
    void Update(float deltaTime) override;
    void Draw() override;

    // Enemy specific methods
    void EnemyAttack();
    bool IsAttackComplete() const;
    void ResetAttackState();
private:
    // Enemy specific properties
    float attackTimer;
    float attackDuration;

    // Reference to components for ease of access
    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<CombatComponent> combatComponent;

    // Textures for the enemy
    TextureHandler textureHandler;
};



#endif //ENEMYENTITY_HPP
