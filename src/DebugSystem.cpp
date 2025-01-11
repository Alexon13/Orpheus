#include "DebugSystem.h"

DebugSystem::DebugSystem(SDL_Renderer* renderer, EntityManager& em, ComponentManager& cm)
    : renderer(renderer), entityManager(em), componentManager(cm) {}

// Toggle debug mode
void DebugSystem::toggleDebug() {
    debugEnabled = !debugEnabled;
}

// Render debug information for all entities
void DebugSystem::render() {
    if (!debugEnabled) {
        return;
    }
    for (Entity entity : entityManager.getEntities()) {
        Position* pos = componentManager.getComponent<Position>(entity);
        Size* size = componentManager.getComponent<Size>(entity);
        Velocity* vel = componentManager.getComponent<Velocity>(entity);
        Force* force = componentManager.getComponent<Force>(entity);

        if (pos && size) {
            drawCollisionBox(pos, size); // Draw collision box
        }

        if (pos && vel && size) {
            drawVelocityVector(pos, vel, size); // Draw velocity vector
        }

        if (pos && force && size) {
            drawForceVector(pos, force, size); // Draw force vector
        }
    }
}

// Draw a collision box around the entity
void DebugSystem::drawCollisionBox(Position* pos, Size* size) {
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
void DebugSystem::drawVelocityVector(Position* pos, Velocity* vel, Size* size) {
    int startX = static_cast<int>(pos->x + (size->width / 2)); // Assuming center of entity
    int startY = static_cast<int>(pos->y + (size->height / 2));
    int endX = startX + static_cast<int>(vel->dx * 7); // Scale for better visualization
    int endY = startY + static_cast<int>(vel->dy * 7);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for velocity vectors
    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

// Draw the force vector
void DebugSystem::drawForceVector(Position* pos, Force* force, Size* size) {
    int startX = static_cast<int>(pos->x + (size->width / 2)); // Assuming center of entity
    int startY = static_cast<int>(pos->y + (size->height / 2));
    int endX = startX + static_cast<int>(force->fx * 3); // Scale for better visualization
    int endY = startY + static_cast<int>(force->fy * 3);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for force vectors
    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}