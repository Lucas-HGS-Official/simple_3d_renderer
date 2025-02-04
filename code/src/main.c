#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window();
void setup(void);
void process_input(bool* isRunning);
void update(void);
void render();

int main(int argc, char const *argv[]) {
    bool isRunning = false;

    isRunning = initialize_window();

    setup();

    while (isRunning) {
        process_input(&isRunning);
        update();
        render();
    }

    return 0;
}

bool initialize_window() {
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

void setup() {

}

void process_input(bool* isRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        *isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            *isRunning = false;
        break;
    default:
        break;
    }
}

void update() {

}

void render() {
    SDL_SetRenderDrawColor(renderer, 46, 136, 87, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}