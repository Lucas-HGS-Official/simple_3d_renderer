#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t trianglesToRender[NUM_MESH_FACES];

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

    for (int i = 0; i < NUM_MESH_FACES; i++) {
        face_t meshFace = meshFaces[i];

        vec3_t faceVertices[3];
        faceVertices[0] = meshVertices[meshFace.a - 1];
        faceVertices[1] = meshVertices[meshFace.b - 1];
        faceVertices[2] = meshVertices[meshFace.c - 1];

        triangle_t projectedTriangle;

        for (int j = 0; j < 3; j++) {
            vec3_t transformedVertex = faceVertices[j];
            transformedVertex = vec3RotateX(transformedVertex, cubeRotation.x);
            transformedVertex = vec3RotateY(transformedVertex, cubeRotation.y);
            transformedVertex = vec3RotateZ(transformedVertex, cubeRotation.z);

            transformedVertex.z -= cameraPos.z;

            vec2_t projectedPoint = project(transformedVertex);

            projectedPoint.x += (windowWidth / 2);
            projectedPoint.y += (windowHeight / 2);

            projectedTriangle.points[j] = projectedPoint;
        }

        trianglesToRender[i] = projectedTriangle;
    }
}

void render() {
    // drawGrid();

    for (int i=0; i<NUM_MESH_FACES; i++) {
        triangle_t triangle = trianglesToRender[i];
        drawRectFilled(triangle.points[0].x, triangle.points[0].y, 4, 4, 0xFFFFFF00);
        drawRectFilled(triangle.points[1].x, triangle.points[1].y, 4, 4, 0xFFFFFF00);
        drawRectFilled(triangle.points[2].x, triangle.points[2].y, 4, 4, 0xFFFFFF00);

        drawTriangle(
            triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            triangle.points[2].x, triangle.points[2].y,
            0xFF00FF00
        );
    }

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}