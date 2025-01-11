#pragma once
#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"

using Entity = std::size_t;
const Entity INVALID_ENTITY = static_cast<Entity>(-1); // Used to prevent null access

class InputSystem {
private:
    EntityManager& entityManager;
    ComponentManager& componentManager;

    Entity controllableEntity = INVALID_ENTITY; // The entity controlled by the player
    bool isJumping = false;

    const float groundLevel = 600.0f; // Y-coordinate for the ground

public:
    InputSystem(EntityManager& em, ComponentManager& cm);

    void setControllableEntity(Entity entity);
    void handleInput(float deltaTime, SDL_Event& event);
};