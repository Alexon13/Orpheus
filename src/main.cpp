#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "PhysicsSystem.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - Physics System (Earth Gravity)",
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
    PhysicsSystem physicsSystem;

    // Create an entity with physics components
    Entity entity1 = entityManager.createEntity();
    Position pos1 = {100, 100};
    Velocity vel1 = {10, 0};
    Acceleration acc1 = {0, 0};
    Mass mass1 = {1.0f}; // Unit mass

    physicsSystem.addEntity(entity1, &pos1, &vel1, &acc1, &mass1);

    // Main loop
    bool isRunning = true;
    SDL_Event event;
    float deltaTime = 0.016f; // ~60 FPS

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Update physics
        physicsSystem.update(deltaTime);

        // Render entities
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect1 = { static_cast<int>(pos1.x), static_cast<int>(pos1.y), 50, 50 }; // Assuming size is 50x50
        SDL_RenderFillRect(renderer, &rect1);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}