#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "DebugSystem.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - Physics Debugging",
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
    CollisionSystem collisionSystem;
    DebugSystem debugSystem(renderer);

    // Create entities
    Entity entity1 = entityManager.createEntity();
    Position pos1 = {100, 600};
    Velocity vel1 = {650, 0};
    Size size1 = {50, 50};
    Mass mass1 = {1.0f};
    Friction friction1 = {0.05f};
    Force force1 = {0.0f, 0.0f}; // No initial force

    Entity entity2 = entityManager.createEntity();
    Position pos2 = {500, 600};
    Velocity vel2 = {-650, 0};
    Size size2 = {50, 50};
    Mass mass2 = {1.0f};
    Friction friction2 = {0.05f};
    Force force2 = {0.0f, 0.0f};

    physicsSystem.addEntity(entity1, &pos1, &vel1, nullptr, &mass1, &friction1, &force1);
    physicsSystem.addEntity(entity2, &pos2, &vel2, nullptr, &mass2, &friction2, &force2);

    collisionSystem.addEntity(entity1, &pos1, &size1);
    collisionSystem.addEntity(entity2, &pos2, &size2);

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

        // Update physics and handle collisions
        physicsSystem.update(deltaTime, collisionSystem);

        // Render entities and debug info
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Entity1
        SDL_Rect rect1 = { static_cast<int>(pos1.x), static_cast<int>(pos1.y), 50, 50 };
        SDL_RenderFillRect(renderer, &rect1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Entity2
        SDL_Rect rect2 = { static_cast<int>(pos2.x), static_cast<int>(pos2.y), 50, 50 };
        SDL_RenderFillRect(renderer, &rect2);

        // Debug rendering
        debugSystem.drawCollisionBox(&pos1, &size1);
        debugSystem.drawVelocityVector(&pos1, &vel1);
        debugSystem.drawForceVector(&pos1, &force1);

        debugSystem.drawCollisionBox(&pos2, &size2);
        debugSystem.drawVelocityVector(&pos2, &vel2);
        debugSystem.drawForceVector(&pos2, &force2);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}