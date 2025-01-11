#pragma once
#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"

class RenderingSystem {
private:
    SDL_Renderer* renderer;
    EntityManager& entityManager;
    ComponentManager& componentManager;

public:
    RenderingSystem(SDL_Renderer* renderer, EntityManager& em, ComponentManager& cm);

    // Render entites on the screen with random colors
    void render();
};
