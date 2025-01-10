#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "Components.h"
#include "PhysicsSystem.h"
#include "DebugSystem.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine - Work in Progress",
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

    // ECS (Entity-Component System) setup
    EntityManager entityManager;
    ComponentManager componentManager;
    PhysicsSystem physicsSystem(entityManager, componentManager);
    DebugSystem debugSystem(renderer, entityManager, componentManager);

    // Create Entity 1 for testing purposes
    Entity entity1 = entityManager.createEntity();
    componentManager.addComponent(entity1, Position{100, 100});
    componentManager.addComponent(entity1, Velocity{100, 0}); //Initial velocity for testing purposes
    componentManager.addComponent(entity1, Size{50, 50});
    componentManager.addComponent(entity1, Mass{1.0f});
    componentManager.addComponent(entity1, Friction{0});
    componentManager.addComponent(entity1, Force{0.0f, 0.0f});
    physicsSystem.addEntity(entity1);

    // Create Entity 2 for testing purposes
    Entity entity2 = entityManager.createEntity();
    componentManager.addComponent(entity2, Position{500, 100});
    componentManager.addComponent(entity2, Velocity{-50, 0});
    componentManager.addComponent(entity2, Size{50, 50});
    componentManager.addComponent(entity2, Mass{1.0f});
    componentManager.addComponent(entity2, Friction{0});
    componentManager.addComponent(entity2, Force{0.0f, 0.0f});
    physicsSystem.addEntity(entity2);

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
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
                debugSystem.toggleDebug(); // Toggle debug mode with 'D' key
            }
        }

        // Update physics each frame
        physicsSystem.update(deltaTime);

        // Render loop
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render entity1 for testing (TODO: implement with render system later)
        Position* pos1 = componentManager.getComponent<Position>(entity1);
        Size* size1 = componentManager.getComponent<Size>(entity1);
        if (pos1 && size1) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for entity1
            SDL_Rect rect1 = {
                static_cast<int>(pos1->x),
                static_cast<int>(pos1->y),
                static_cast<int>(size1->width),
                static_cast<int>(size1->height)
            };
            SDL_RenderFillRect(renderer, &rect1);
        }

        // Render entity2 for testing (TODO: implement with render system later)
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
