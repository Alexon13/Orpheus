#pragma once
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "CollisionSystem.h"
#include <unordered_set>

class PhysicsSystem {
private:
    std::unordered_set<Entity> entities;
    EntityManager& entityManager;
    ComponentManager& componentManager;
    CollisionSystem collisionSystem;

    float gravity = 9.8f; // Gravity constant

public:
    PhysicsSystem(EntityManager& em, ComponentManager& cm);

    void addEntity(Entity entity);
    void removeEntity(Entity entity);
    // Update the physics with each frame
    void update(float deltaTime);

private:
    // Handle collision between two entities
    void handleCollision(Entity a, Entity b);
};