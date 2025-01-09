#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "CollisionSystem.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - Collision Detection with Movement",
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
    CollisionSystem collisionSystem;

    // Create entities
    Entity entity1 = entityManager.createEntity();
    Position pos1 = {100, 100};
    Size size1 = {50, 50};
    Velocity vel1 = {2, 2}; // Entity1 moves diagonally
    collisionSystem.addEntity(entity1, &pos1, &size1);

    Entity entity2 = entityManager.createEntity();
    Position pos2 = {400, 300}; // Stationary entity
    Size size2 = {50, 50};
    Velocity vel2 = {0, 0}; // No velocity for entity2
    collisionSystem.addEntity(entity2, &pos2, &size2);

    // Main loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Update entity1 position using its velocity
        pos1.x += vel1.dx;
        pos1.y += vel1.dy;

        // Collision detection
        collisionSystem.checkCollisions([](Entity a, Entity b) {
            std::cout << "Collision detected between Entity " << a << " and Entity " << b << std::endl;
        });

        // Render entities
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Entity1 (moving)
        SDL_Rect rect1 = { static_cast<int>(pos1.x), static_cast<int>(pos1.y), static_cast<int>(size1.width), static_cast<int>(size1.height) };
        SDL_RenderFillRect(renderer, &rect1);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Entity2 (stationary)
        SDL_Rect rect2 = { static_cast<int>(pos2.x), static_cast<int>(pos2.y), static_cast<int>(size2.width), static_cast<int>(size2.height) };
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);

        // Simple boundary check to prevent entity1 from going off-screen
        if (pos1.x < 0 || pos1.x + size1.width > 800) vel1.dx = -vel1.dx;
        if (pos1.y < 0 || pos1.y + size1.height > 600) vel1.dy = -vel1.dy;
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}