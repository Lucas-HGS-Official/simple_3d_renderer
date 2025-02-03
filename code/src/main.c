#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool initialize_window(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char const *argv[]) {
    bool isRunning = false;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    isRunning = initialize_window(window, renderer);

    return 0;
}

bool initialize_window(SDL_Window* window, SDL_Renderer* renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        
        return false;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_BORDERLESS
    );
    if(!window) {
        fprintf(stderr, "Error creating the SDL Window.\n");

        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");

        return false;
    }

    return true;
}