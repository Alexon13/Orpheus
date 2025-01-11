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
    InputSystem(EntityManager& em, ComponentManager& cm)
        : entityManager(em), componentManager(cm), controllableEntity(0) {}

    void setControllableEntity(Entity entity) {
        controllableEntity = entity;
    }

    void handleInput(float deltaTime, SDL_Event& event) {
        if (controllableEntity == INVALID_ENTITY) return;

        Velocity* vel = componentManager.getComponent<Velocity>(controllableEntity);
        Position* pos = componentManager.getComponent<Position>(controllableEntity);
        Size* size = componentManager.getComponent<Size>(controllableEntity);

        if (vel && pos && size) {
            // Horizontal movement
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) {
                    vel->dx = -50; // Move left (A)
                } else if (event.key.keysym.sym == SDLK_d) {
                    vel->dx = 50; // Move right (D)
                }
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    vel->dx = 0; // Stop horizontal movement when key is released
                }
            }

            // Jumping logic
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isJumping) {
                vel->dy = -50; // Jump velocity
                isJumping = true;
            }

            // Reset jumping when entity lands
            if (pos->y + size->height >= groundLevel) {
                pos->y = groundLevel - size->height; // Correct position to ground level
                isJumping = false;                   // Allow jumping again
            }
        }
    }
};