#include <SDL2/SDL.h>
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "WindowManager.h"
#include "PhysicsSystem.h"
#include "SpawningSystem.h"
#include "DebugSystem.h"
#include "InputSystem.h"
#include "RenderingSystem.h"
#include <iostream>
#include <chrono>

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 900

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
    WindowManager windowManager;
    PhysicsSystem physicsSystem(entityManager, componentManager, windowManager);
    SpawningSystem spawningSystem(entityManager, componentManager, physicsSystem);
    DebugSystem debugSystem(renderer, entityManager, componentManager);
    InputSystem inputSystem(entityManager, componentManager, physicsSystem, windowManager, debugSystem);
    RenderingSystem renderingSystem(renderer, entityManager, componentManager);

    // Set the size of the default window for testing purposes
    windowManager.setScreenWidth(WINDOW_WIDTH);
    windowManager.setScreenHeight(WINDOW_HEIGHT);

    // Spawn several entities (including controllable) for testing purposes
    // (x, y, dx, dy, width, height, mass)
    Entity entity1 = spawningSystem.spawnEntity(100, 100, 0, 0, 50, 50, 1.0f);
    Entity entity2 = spawningSystem.spawnEntity(200, 100, 0, 0, 50, 50, 1.0f);
    Entity entity3 = spawningSystem.spawnEntity(300, 100, 0, 0, 50, 50, 1.0f);
    Entity entity4 = spawningSystem.spawnEntity(400, 100, 0, 0, 50, 50, 1.0f);
    Entity entity5 = spawningSystem.spawnEntity(500, 100, 0, 0, 50, 50, 1.0f);
    Entity entity6 = spawningSystem.spawnEntity(600, 100, 0, 0, 50, 50, 1.0f);
    Entity entity7 = spawningSystem.spawnEntity(700, 100, 0, 0, 50, 50, 1.0f);
    Entity entity8 = spawningSystem.spawnEntity(800, 100, 0, 0, 50, 50, 1.0f);

    // Set one of the entities as controllable (Can't have more than one at the moment!)
    inputSystem.setControllableEntity(entity8);

    // Program flow parameters
    bool isRunning = true;
    SDL_Event event;
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint previousFrameTime = Clock::now();

    // Game Loop
    while (isRunning) {
        // Get current time
        TimePoint currentFrameTime = Clock::now();

        // Calculate deltaTime in seconds (float)
        std::chrono::duration<float> delta = currentFrameTime - previousFrameTime;
        float deltaTime = delta.count();  // deltaTime in seconds

        previousFrameTime = currentFrameTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } 
            else {
                // Pass the event to the InputSystem and handle input
                inputSystem.handleInput(deltaTime, event);
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