#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Rectangle dimensions and speed
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 100;
const int SPEED = 5;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Orpheus Engine", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Rectangle position
    SDL_Rect rect = { 200, 150, RECT_WIDTH, RECT_HEIGHT };

    // Key states (pressed or not)
    std::unordered_map<SDL_Keycode, bool> keyState;

    // Main loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else if (event.type == SDL_KEYDOWN) {
                keyState[event.key.keysym.sym] = true;
            } else if (event.type == SDL_KEYUP) {
                keyState[event.key.keysym.sym] = false;
            }
        }

        // Smooth movement
        if (keyState[SDLK_UP]) {
            rect.y -= SPEED;
        }
        if (keyState[SDLK_DOWN]) {
            rect.y += SPEED;
        }
        if (keyState[SDLK_LEFT]) {
            rect.x -= SPEED;
        }
        if (keyState[SDLK_RIGHT]) {
            rect.x += SPEED;
        }

        // Prevent the rectangle from moving off-screen
        if (rect.x < 0) rect.x = 0;
        if (rect.y < 0) rect.y = 0;
        if (rect.x + rect.w > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - rect.w;
        if (rect.y + rect.h > SCREEN_HEIGHT) rect.y = SCREEN_HEIGHT - rect.h;

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen (black)
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Draw red rectangle
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}