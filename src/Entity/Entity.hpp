#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

// Forward declarations
class Component;

class Entity {
public:
    Entity();
    virtual ~Entity();

    // Core functions
    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Draw();

    // Turn-based mechanics
    virtual void StartTurn();
    virtual bool IsActionComplete();
    virtual void ResetActionState();

    // Component management
    void AddComponent(std::shared_ptr<Component> component);
    template <typename T>
    std::shared_ptr<T> GetComponent();

    // Common properties
    Vector2 GetPosition() const { return position; }
    void SetPosition(Vector2 pos) { position = pos; }
    Rectangle GetCollisionRect() const { return collisionRec; }

    // Entity type identification
    std::string GetType() const { return entityType; }
    void SetType(const std::string& type) { entityType = type; }

    // Health management
    int GetHealth() const { return health; }
    void SetHealth(int value) { health = value; }
    void TakeDamage(int damage);
    bool IsDead() const { return health <= 0; }
    bool actionCompletedThisTurn;

protected:
    Vector2 position;
    Rectangle collisionRec;
    std::string entityType;
    int health;


    std::vector<std::shared_ptr<Component>> components;
};

// Template implementation
template <typename T>
std::shared_ptr<T> Entity::GetComponent() {
    for (auto& component : components) {
        std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(component);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

#endif // ENTITY_HPP