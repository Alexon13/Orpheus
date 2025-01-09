#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "MovementSystem.h"

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
    MovementSystem movementSystem;

    // Create entities
    Entity entity1 = entityManager.createEntity();
    Position pos1 = {100, 100};
    Velocity vel1 = {50, 0}; // Moving right
    movementSystem.addEntity(entity1, &pos1, &vel1);

    Entity entity2 = entityManager.createEntity();
    Position pos2 = {200, 200};
    Velocity vel2 = {0, 50}; // Moving down
    movementSystem.addEntity(entity2, &pos2, &vel2);

    // Game loop
    bool isRunning = true;
    SDL_Event event;
    float deltaTime = 0.016f; // ~60 FPS

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

        // Render entities as rectangles
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect1 = { static_cast<int>(pos1.x), static_cast<int>(pos1.y), 50, 50 };
        SDL_RenderFillRect(renderer, &rect1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect rect2 = { static_cast<int>(pos2.x), static_cast<int>(pos2.y), 50, 50 };
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}