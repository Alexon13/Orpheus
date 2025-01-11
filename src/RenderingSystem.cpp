#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(SDL_Renderer* renderer, EntityManager& em, ComponentManager& cm)
    : renderer(renderer), entityManager(em), componentManager(cm) {}

// Render entites on the screen with random colors
void RenderingSystem::render() {
    for (Entity entity : entityManager.getEntities()) {
        Position* pos = componentManager.getComponent<Position>(entity);
        Size* size = componentManager.getComponent<Size>(entity);

        if (pos && size) {
            // Generate a distinct, non-black color for each new entity
            Uint8 r = (entity * 30 + 80) % 255; // Ensure value is not too low (so it's not black)
            Uint8 g = (entity * 70 + 80) % 255;
            Uint8 b = (entity * 90 + 80) % 255;

            // Set the color and render the entity
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_Rect rect = {
                static_cast<int>(pos->x),
                static_cast<int>(pos->y),
                static_cast<int>(size->width),
                static_cast<int>(size->height)
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}