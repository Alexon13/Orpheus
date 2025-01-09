#pragma once
#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include <iostream>

class DebugSystem {
private:
    SDL_Renderer* renderer;
    EntityManager& entityManager;
    ComponentManager& componentManager;

    bool debugEnabled = false;

public:
    DebugSystem(SDL_Renderer* renderer, EntityManager& em, ComponentManager& cm)
        : renderer(renderer), entityManager(em), componentManager(cm) {}

    // Toggle debug mode
    void toggleDebug() {
        debugEnabled = !debugEnabled;
    }

    // Render debug information for all entities
    void render() {
        if (!debugEnabled) {
            std::cout << "Debug mode is disabled." << std::endl;
            return;
        }
        std::cout << "Debug mode is enabled." << std::endl;
        for (Entity entity : entityManager.getEntities()) {
            Position* pos = componentManager.getComponent<Position>(entity);
            Size* size = componentManager.getComponent<Size>(entity);
            Velocity* vel = componentManager.getComponent<Velocity>(entity);
            Force* force = componentManager.getComponent<Force>(entity);

            if (pos && size) {
                drawCollisionBox(pos, size); // Draw collision box
            }

            if (pos && vel) {
                drawVelocityVector(pos, vel); // Draw velocity vector
            }

            if (pos && force) {
                drawForceVector(pos, force); // Draw force vector
            }
        }
    }

    // Draw a collision box around the entity
    void drawCollisionBox(Position* pos, Size* size) {
        SDL_Rect rect = {
            static_cast<int>(pos->x),
            static_cast<int>(pos->y),
            static_cast<int>(size->width),
            static_cast<int>(size->height)
        };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for collision boxes
        SDL_RenderDrawRect(renderer, &rect);
    }

    // Draw the velocity vector
    void drawVelocityVector(Position* pos, Velocity* vel) {
        int startX = static_cast<int>(pos->x + 25); // Assuming center for a 50x50 size entity
        int startY = static_cast<int>(pos->y + 25);
        int endX = startX + static_cast<int>(vel->dx * 10); // Scale for visualization
        int endY = startY + static_cast<int>(vel->dy * 10);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for velocity vectors
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }

    // Draw the force vector
    void drawForceVector(Position* pos, Force* force) {
        int startX = static_cast<int>(pos->x + 25); // Assuming center for a 50x50 size entity
        int startY = static_cast<int>(pos->y + 25);
        int endX = startX + static_cast<int>(force->fx * 0.1); // Scale for visualization
        int endY = startY + static_cast<int>(force->fy * 0.1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for force vectors
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }
};