#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "MovementSystem.h"
#include "RenderingSystem.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - ECS",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // ECS setup
    EntityManager entityManager;
    ComponentManager componentManager;
    MovementSystem movementSystem;
    RenderingSystem renderingSystem(renderer);

    // Create entities
    Entity entity1 = entityManager.createEntity();
    Position pos1 = {100, 100};
    Velocity vel1 = {50, 0};
    componentManager.addComponent(entity1, pos1);
    componentManager.addComponent(entity1, vel1);
    movementSystem.addEntity(entity1, componentManager.getComponent<Position>(entity1), componentManager.getComponent<Velocity>(entity1));
    renderingSystem.addEntity(entity1, componentManager.getComponent<Position>(entity1));

    // Main loop
    bool isRunning = true;
    SDL_Event event;
    float deltaTime = 0.016f;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Update
        movementSystem.update(deltaTime);

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderingSystem.render();
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}