
#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Entity;
class PlayerEntity;
class EnemyEntity;

class Game {
public:
    Game();
    ~Game();

    void Init();
    void Update(float deltaTime);

private:
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
    void HandlePlayerTurn();
    void HandleEnemyTurn();
    void SwitchToPlayerTurn();
    void SwitchToEnemyTurn();
    void DrawUI();

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
