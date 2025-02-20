#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

vec3_t cubeRotation = { 0, 0, 0 };

vec3_t cameraPos = { 0, 0, -5 };
float FOVFactor = 640;

int previousFrameTime = 0;

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
        .x = (FOVFactor * point.x) / point.z,
        .y = (FOVFactor * point.y) / point.z
    };
    return projectedPoint;
}
void update() {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }
    
    previousFrameTime = SDL_GetTicks();

    cubeRotation.x += 0.005;
    cubeRotation.y += 0.005;
    cubeRotation.z += 0.005;

    // for (int i = 0; i < N_POINTS; i++) {
    //     vec3_t point = cubePoints[i];

    //     vec3_t transformedPoint = vec3RotateX(point, cubeRotation.x);
    //     transformedPoint = vec3RotateY(transformedPoint, cubeRotation.y);
    //     transformedPoint = vec3RotateZ(transformedPoint, cubeRotation.z);

    //     transformedPoint.z -= cameraPos.z;

    //     vec2_t projectedPoint = project(transformedPoint);

    //     projectedPoints[i] = projectedPoint;
    // }
}

void render() {
    // drawGrid();

    // for (int i=0; i<N_POINTS; i++) {
    //     vec2_t projectedPoint = projectedPoints[i];
    //     drawRectFilled(
    //         projectedPoint.x + (windowWidth / 2),
    //         projectedPoint.y + (windowHeight / 2),
    //         4, 4,
    //         0xFFFFFF00);
    // }

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}