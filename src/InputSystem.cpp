#include "InputSystem.h"

InputSystem::InputSystem(EntityManager& em, ComponentManager& cm, PhysicsSystem& ps, WindowManager& wm, DebugSystem& ds)
    : entityManager(em), componentManager(cm), physicsSystem(ps), windowManager(wm), debugSystem(ds), controllableEntity(0) {}

void InputSystem::setControllableEntity(Entity entity) {
    controllableEntity = entity;
}

void InputSystem::handleInput(float deltaTime, SDL_Event& event) {
    int groundLevel = windowManager.getScreenHeight();
    if (controllableEntity == INVALID_ENTITY) return;

    Velocity* vel = componentManager.getComponent<Velocity>(controllableEntity);
    Position* pos = componentManager.getComponent<Position>(controllableEntity);
    Size* size = componentManager.getComponent<Size>(controllableEntity);

    if (vel && pos && size) {
        // Horizontal movement
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_a) {
                vel->dx = -50; // Move left with 'A' key
            } else if (event.key.keysym.sym == SDLK_d) {
                vel->dx = 50; // Move right with 'D' key
            }
        }

        // Toggle debug mode with 'X' key
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x) {
            debugSystem.toggleDebug();
        } 

        // Enable/Disable Gravity with 'G' key
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g) {
            physicsSystem.toggleGravity();
        }

        // Jumping logic; press 'SPACE' key
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