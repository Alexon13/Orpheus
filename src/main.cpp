#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PhysicsSystem.h"
#include "SpawningSystem.h"
#include "InputSystem.h"
#include "DebugSystem.h"
#include "RenderingSystem.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAME_RATE 0.008f // ~120 FPS

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
    SpawningSystem spawningSystem(entityManager, componentManager, physicsSystem);
    InputSystem inputSystem(entityManager, componentManager);
    DebugSystem debugSystem(renderer, entityManager, componentManager);
    RenderingSystem renderingSystem(renderer, entityManager, componentManager);

    // Spawn several entities (including controllable) for testing purposes
    // (x, y, dx, dy, width, height, mass)
    Entity entity1 = spawningSystem.spawnEntity(0, 100, 0, 0, 50, 50, 1.0f);
    Entity entity2 = spawningSystem.spawnEntity(100, 100, 0, 0, 50, 50, 1.0f);
    Entity entity3 = spawningSystem.spawnEntity(200, 100, 0, 0, 50, 50, 1.0f);

    // Set one of the entities as controllable (Can't have more than one at the moment!)
    inputSystem.setControllableEntity(entity1);

    // Program flow parameters
    bool isRunning = true;
    SDL_Event event;
    float deltaTime = FRAME_RATE;

    // Check for entity collisions
    auto onCollision = [](Entity a, Entity b) {
        std::cout << "Collision detected between Entity " << a << " and Entity " << b << std::endl;
    };

    // Game Loop
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } 
            else {
                // Pass the event to the InputSystem and handle input
                inputSystem.handleInput(deltaTime, event);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x) {
                debugSystem.toggleDebug(); // Toggle debug mode with 'X' key
            } 
        }

        // Update physics each frame
        physicsSystem.update(deltaTime);

        // Render loop
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render all entities using the Render System
        renderingSystem.render();

        // Render debug system info
        debugSystem.render();

        // Present the frame
        SDL_RenderPresent(renderer);
    }

    // Final cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}