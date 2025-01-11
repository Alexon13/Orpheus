#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PhysicsSystem.h"

class SpawningSystem {
private:
    EntityManager& entityManager;
    ComponentManager& componentManager;
    PhysicsSystem& physicsSystem;

public:
    SpawningSystem(EntityManager& em, ComponentManager& cm, PhysicsSystem& ps)
        : entityManager(em), componentManager(cm), physicsSystem(ps) {}

    // Spawn an entity with defined components
    Entity spawnEntity(float x, float y, float dx, float dy, float width, float height, float mass, float friction = 0.0f) {
        Entity entity = entityManager.createEntity();

        componentManager.addComponent(entity, Position{x, y});
        componentManager.addComponent(entity, Velocity{dx, dy});
        componentManager.addComponent(entity, Size{width, height});
        componentManager.addComponent(entity, Mass{mass});
        componentManager.addComponent(entity, Friction{friction});
        componentManager.addComponent(entity, Force{0.0f, 0.0f}); // Set to 0 initially (TODO: Implement MovementSystem)

        physicsSystem.addEntity(entity);

        return entity;
    }
};