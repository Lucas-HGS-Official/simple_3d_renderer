#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer);
void processInput(bool* isRunning);
void update(void);
void render();

int main(int argc, char const *argv[]) {
    bool isRunning = false;

    isRunning = initializeWindow();

    setup(windowWidth, windowHeight, &renderer);

    while (isRunning) {
        processInput(&isRunning);
        update();
        render(windowWidth, windowHeight, &renderer);
    }

    destroyWindow();

    return 0;
}

void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer) {
    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);

    colorBufferTexture = SDL_CreateTexture(
        *renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );
}

void processInput(bool* isRunning) {
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

    drawGrid();
    drawRectFilled(300, 200, 300, 150, 0xFFFF00FF);
    drawPixel(20, 20, 0xFFFF00FF);

    renderColorBuffer();
    clearColorBuffer(0xFFFF0000);

    SDL_RenderPresent(renderer);
}