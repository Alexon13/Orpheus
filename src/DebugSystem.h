#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include "Components.h"

class DebugSystem {
private:
    SDL_Renderer* renderer;

public:
    explicit DebugSystem(SDL_Renderer* renderer) : renderer(renderer) {}

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

    void drawVelocityVector(Position* pos, Velocity* vel) {
        int startX = static_cast<int>(pos->x + 25); // Center of the entity (assuming size 50x50)
        int startY = static_cast<int>(pos->y + 25);
        int endX = startX + static_cast<int>(vel->dx * 10); // Scale velocity for better visualization
        int endY = startY + static_cast<int>(vel->dy * 10);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for velocity vectors
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }

    void drawForceVector(Position* pos, Force* force) {
        int startX = static_cast<int>(pos->x + 25); // Center of the entity
        int startY = static_cast<int>(pos->y + 25);
        int endX = startX + static_cast<int>(force->fx * 0.1); // Scale force for better visualization
        int endY = startY + static_cast<int>(force->fy * 0.1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for force vectors
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }
};