#pragma once
#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PhysicsSystem.h"

using Entity = std::size_t;
const Entity INVALID_ENTITY = static_cast<Entity>(-1); // Used to prevent null access

class InputSystem {
private:
    EntityManager& entityManager;
    ComponentManager& componentManager;
    PhysicsSystem& physicsSystem;

    Entity controllableEntity = INVALID_ENTITY; // The entity controlled by the player
    bool isJumping = false;

    const float groundLevel = 600.0f; // Y-coordinate for the ground

public:
    InputSystem(EntityManager& em, ComponentManager& cm, PhysicsSystem& ps);

    void setControllableEntity(Entity entity);
    void handleInput(float deltaTime, SDL_Event& event);
};