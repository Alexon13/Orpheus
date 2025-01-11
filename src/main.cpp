#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Components.h"
#include "PhysicsSystem.h"
#include "DebugSystem.h"
#include "SpawningSystem.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - Work in Progress",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
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

    // ECS (Entity-Component System) setup
    EntityManager entityManager;
    ComponentManager componentManager;
    PhysicsSystem physicsSystem(entityManager, componentManager);
    DebugSystem debugSystem(renderer, entityManager, componentManager);
    SpawningSystem spawningSystem(entityManager, componentManager, physicsSystem);

    // Spawn two entities for testing purposes
    Entity entity1 = spawningSystem.spawnEntity(100, 100, 100, 0, 50, 50, 1.0f);
    Entity entity2 = spawningSystem.spawnEntity(500, 100, -100, 0, 50, 50, 1.0f);

    bool isRunning = true;
    SDL_Event event;
    float deltaTime = 0.032f; // ~60 FPS

    auto onCollision = [](Entity a, Entity b) {
        std::cout << "Collision detected between Entity " << a << " and Entity " << b << std::endl;
    };

    // Game Loop
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x) {
                debugSystem.toggleDebug(); // Toggle debug mode with 'X' key
            }
        }

        // Update physics each frame
        physicsSystem.update(deltaTime);

        // Render loop
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render entity1 for testing (TODO: implement with RenderingSystem later)
        Position* pos1 = componentManager.getComponent<Position>(entity1);
        Size* size1 = componentManager.getComponent<Size>(entity1);
        if (pos1 && size1) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Magenta for entity1
            SDL_Rect rect1 = {
                static_cast<int>(pos1->x),
                static_cast<int>(pos1->y),
                static_cast<int>(size1->width),
                static_cast<int>(size1->height)
            };
            SDL_RenderFillRect(renderer, &rect1);
        }

        // Render entity2 for testing (TODO: implement with RenderingSystem later)
        Position* pos2 = componentManager.getComponent<Position>(entity2);
        Size* size2 = componentManager.getComponent<Size>(entity2);
        if (pos2 && size2) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for entity2
            SDL_Rect rect2 = {
                static_cast<int>(pos2->x),
                static_cast<int>(pos2->y),
                static_cast<int>(size2->width),
                static_cast<int>(size2->height)
            };
            SDL_RenderFillRect(renderer, &rect2);
        }

        // Render debug system info
        debugSystem.render();

        SDL_RenderPresent(renderer);
    }

    // Final cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
