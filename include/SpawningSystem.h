#pragma once
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PhysicsSystem.h"

class SpawningSystem {
private:
    EntityManager& entityManager;
    ComponentManager& componentManager;
    PhysicsSystem& physicsSystem;

public:
    SpawningSystem(EntityManager& em, ComponentManager& cm, PhysicsSystem& ps);

    // Spawn an entity with defined components
    Entity spawnEntity(float x, float y, float dx, float dy, float width, float height, float mass, float friction = 0.0f);
};