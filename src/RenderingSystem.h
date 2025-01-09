// TODO: Complete System and integrate with the rest!
#pragma once
#include <SDL2/SDL.h>
#include "Components.h"
#include <unordered_map>

class RenderingSystem {
private:
    SDL_Renderer* renderer;
    std::unordered_map<Entity, Position*> positions;

public:
    explicit RenderingSystem(SDL_Renderer* renderer) : renderer(renderer) {}

    void addEntity(Entity entity, Position* pos) {
        positions[entity] = pos;
    }

    void render() {
        for (const auto& [entity, pos] : positions) {
            SDL_Rect rect = { static_cast<int>(pos->x), static_cast<int>(pos->y), 50, 50 };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};