//
// Created by Jason Evans on 24/03/2025.
//

#include "Entity.hpp"
#include "Component.hpp"
#include <iostream>

Entity::Entity() :
health(100),
actionCompletedThisTurn(false)
{
    position = {0.0f, 0.0f};
    collisionRec = {0.0f, 0.0f, 0.0f, 0.0f};
}

Entity::~Entity() {
    components.clear();
}

void Entity::Init()
{
    for (auto& component : components)
    {
        component->Init(this);
    }
}

void Entity::Update(float deltaTime)
{
    for (auto& component : components)
    {
        component->Update(this,deltaTime);
    }

    // Update collision rectangle based on current position
    collisionRec.x = position.x;
    collisionRec.y = position.y;
}

void Entity::Draw()
{
    for (auto& component : components)
    {
        std::cout << "Entity::Draw() called for " << entityType
                << " with " << components.size() << " components" << std::endl;

        // Draw a colored rectangle to represent the entity's position and size


        component->Draw(this);

    }
}

void Entity::StartTurn()
{
    actionCompletedThisTurn = false;
    std::cout << entityType << " starting turn" << std::endl;
}

bool Entity::IsActionComplete() {
    return actionCompletedThisTurn;
}

void Entity::ResetActionState() {
    actionCompletedThisTurn = false;
}

void Entity::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

void Entity::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

    std::cout << entityType << " took " << damage << " damage. Health: " << health << std::endl;
}



