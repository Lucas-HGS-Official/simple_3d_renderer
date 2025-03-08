#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t* trianglesToRender = NULL;

vec3_t cameraPos = { 0, 0, 0 };
float FOVFactor = 640;

int previousFrameTime = 0;

void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer);
void processInput(bool* isRunning);
vec2_t project(vec3_t point);
void update(void);
void render(void);
void freeResources(void);

int main(int argc, char const *argv[]) {
    bool isRunning = false;

    isRunning = initializeWindow();

    setup(windowWidth, windowHeight, &renderer);

    while (isRunning) {
        processInput(&isRunning);
        update();
        render();
    }

    destroyWindow();
    freeResources();

    return 0;
}

void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer) {
    render_method = RENDER_WIRE;
    cull_method = CULL_BACKFACE;

    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);

    colorBufferTexture = SDL_CreateTexture(
        *renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );

    //loadObjFileData("./assets/f22.obj");
    loadCubeMeshData();
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
        if (event.key.keysym.sym == SDLK_1)
            render_method = RENDER_WIRE_VERTEX;
        if (event.key.keysym.sym == SDLK_2)
            render_method = RENDER_WIRE;
        if (event.key.keysym.sym == SDLK_3)
            render_method = RENDER_FILL_TRIANGLE;
        if (event.key.keysym.sym == SDLK_4)
            render_method = RENDER_FILL_TRIANGLE_WIRE;
        if (event.key.keysym.sym == SDLK_c)
            cull_method = CULL_BACKFACE;
        if (event.key.keysym.sym == SDLK_d)
            cull_method = CULL_NONE;
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

    trianglesToRender = NULL;
    
    previousFrameTime = SDL_GetTicks();

    mesh.rotation.x += 0.005;
    mesh.rotation.y += 0.005;
    mesh.rotation.z += 0.005;

    int numFaces = array_length(mesh.faces);
    for (int i = 0; i < numFaces; i++) {
        face_t meshFace = mesh.faces[i];

        vec3_t faceVertices[3];
        faceVertices[0] = mesh.vertices[meshFace.a - 1];
        faceVertices[1] = mesh.vertices[meshFace.b - 1];
        faceVertices[2] = mesh.vertices[meshFace.c - 1];

        vec3_t transformedVertices[3];

        for (int j = 0; j < 3; j++) {
            vec3_t transformedVertex = faceVertices[j];
            transformedVertex = vec3RotateX(transformedVertex, mesh.rotation.x);
            transformedVertex = vec3RotateY(transformedVertex, mesh.rotation.y);
            transformedVertex = vec3RotateZ(transformedVertex, mesh.rotation.z);

            transformedVertex.z += 5;

            transformedVertices[j] = transformedVertex;
        }

        if (cull_method == CULL_BACKFACE) {
            vec3_t vectorA = transformedVertices[0];
            vec3_t vectorB = transformedVertices[1];
            vec3_t vectorC = transformedVertices[2];
    
            vec3_t vectorAB = vec3Subtraction(vectorB, vectorA);
            vec3Normalize(&vectorAB);
            vec3_t vectorAC = vec3Subtraction(vectorC, vectorA);
            vec3Normalize(&vectorAC);
    
            vec3_t faceNormal = vec3CrossProduct(vectorAB, vectorAC);
    
            vec3Normalize(&faceNormal);
    
            vec3_t cameraRay = vec3Subtraction(cameraPos, vectorA);
    
            float dotNormalCamera = vec3DotProduct(cameraRay, faceNormal);
    
            if (dotNormalCamera < 0) continue;
        }

        

        vec2_t projectedPoints[3];

        for (int j = 0; j < 3; j++) {
            
            projectedPoints[j] = project(transformedVertices[j]);
            
            projectedPoints[j].x += (windowWidth / 2);
            projectedPoints[j].y += (windowHeight / 2);
        }

        triangle_t projectedTriangle = {
            .points = {
                { projectedPoints[0].x, projectedPoints[0].y },
                { projectedPoints[1].x, projectedPoints[1].y },
                { projectedPoints[2].x, projectedPoints[2].y }
            },
            .color = meshFace.color
        };
            
        array_push(trianglesToRender, projectedTriangle);
    }
}

void render() {
    SDL_RenderClear(renderer);

    // drawGrid();
    
    int numFaces = array_length(trianglesToRender);
    for (int i=0; i<numFaces; i++) {
        triangle_t triangle = trianglesToRender[i];

        if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE) {
            drawTriangleFilled(
                triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y,
                triangle.color
            );
        }
        if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE) {
            drawTriangle(
                triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y,
                0xFFFFFFFF
            );
        }
        if (render_method == RENDER_WIRE_VERTEX) {           
            drawRectFilled(triangle.points[0].x - 2, triangle.points[0].y - 2, 4, 4, 0xFFFF0000);
            drawRectFilled(triangle.points[1].x - 2, triangle.points[1].y - 2, 4, 4, 0xFFFF0000);
            drawRectFilled(triangle.points[2].x - 2, triangle.points[2].y - 2, 4, 4, 0xFFFF0000);
        }
    }

    array_free(trianglesToRender);

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void freeResources(void) {
    free(colorBuffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}