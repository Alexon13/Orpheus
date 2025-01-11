#pragma once
#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include <iostream>

class DebugSystem {
private:
    SDL_Renderer* renderer;
    EntityManager& entityManager;
    ComponentManager& componentManager;

    bool debugEnabled = false;

public:
    DebugSystem(SDL_Renderer* renderer, EntityManager& em, ComponentManager& cm);

    // Toggle debug mode
    void toggleDebug();

    // Render debug information for all entities
    void render();

    // Draw a collision box around the entity
    void drawCollisionBox(Position* pos, Size* size);

    // Draw the velocity vector
    void drawVelocityVector(Position* pos, Velocity* vel, Size* size);

    // Draw the force vector
    void drawForceVector(Position* pos, Force* force, Size* size);
};