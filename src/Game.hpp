
#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <string>

#include "TextureHandler.hpp"

// Forward declarations
class Entity;
class PlayerEntity;
class EnemyEntity;

enum class GameState
{
    EXPLORATION,
    COMBAT,
    TRANSITION_TO_COMBAT,
    TRANSITION_TO_EXPLORATION
};

class Game {
public:
    TextureHandler textureHandler;
    Game();
    ~Game();

    void Init();
    void Update(float deltaTime);
    void Draw();

private:
    GameState currentState;
    float stateTransitionTimer;
    const float TRANSITION_DURATION = 0.5f;  // Half a second transition

    // Entities
    std::shared_ptr<PlayerEntity> player;
    std::shared_ptr<EnemyEntity> enemy;
    std::vector<std::shared_ptr<Entity>> entities;

    // Turn-based game state
    bool isPlayerTurn;
    bool isEnemyTurn;
    bool playerTurnInitialized;
    bool enemyTurnInitialized;

    // Game methods
    void HandleExplorationMode(float deltaTime);
    void HandleCombatMode(float deltaTime);
    void CheckCollisions();
    void TransitionToCombat();
    void TransitionToExploration();
    void HandlePlayerTurn();
    void HandleEnemyTurn();
    void SwitchToPlayerTurn();
    void SwitchToEnemyTurn();
    void DrawUI();
    void CheckEntityHealth();
    void SpawnNewEnemy();

    // Entity management
    void AddEntity(std::shared_ptr<Entity> entity);
    template <typename T>
    std::shared_ptr<T> GetEntity();
};

// Template implementation
template <typename T>
std::shared_ptr<T> Game::GetEntity() {
    for (auto& entity : entities) {
        std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(entity);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

#endif // GAME_HPP
