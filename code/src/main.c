#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

#define N_POINTS (9 * 9 * 9)

vec3_t cubePoints[N_POINTS];
vec2_t projectedPoints[N_POINTS];
vec3_t cubeRotation = { 0, 0, 0 };

vec3_t cameraPos = { 0, 0, -5 };
float FOVFactor = 640;

void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer);
void processInput(bool* isRunning);
vec2_t project(vec3_t point);
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

    int pCount = 0;

    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t newPoint = { x, y, z };
                cubePoints[pCount++] = newPoint;
            }
        }
    }
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

vec2_t project(vec3_t point) {
    vec2_t projectedPoint = {
        (point.x * FOVFactor) / point.z,
        (point.y * FOVFactor) / point.z
    };

    return projectedPoint;
}

void update() {
    cubeRotation.y += 0.1;
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cubePoints[i];

        point.z -= cameraPos.z;

        vec2_t projectedPoint = project(point);

        projectedPoints[i] = projectedPoint;
    }
}

void render() {
    // drawGrid();

    for (int i=0; i<N_POINTS; i++) {
        vec2_t projectedPoint = projectedPoints[i];
        drawRectFilled(
            projectedPoint.x + (windowWidth / 2),
            projectedPoint.y + (windowHeight / 2),
            4, 4,
            0xFFFFFF00);
    }

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}