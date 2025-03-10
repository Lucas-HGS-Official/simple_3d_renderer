#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 800;
int windowHeight = 600;

uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;

bool initializeWindow(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        
        return false;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
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

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void drawPixel(int x, int y, uint32_t color) {
    if (x > 0 && x < windowWidth && y > 0 && y < windowHeight){
        colorBuffer[(windowWidth * y) + x] = color;
    }
}

void drawGrid(void) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            if (x % 10 == 0 || y % 10 == 0) {
                colorBuffer[(windowWidth * y) + x] = 0xFFFFFFFF;
            }
        }
    }
}


void drawRectFilled(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int currentX = x+i;
            int currentY = y+j;
            drawPixel(currentX, currentY, color);
            //colorBuffer[(windowWidth * currentY) + currentX] = color;
        }
    }
}

void drawLine(int x0, int y0, int x1, int y1, uint32_t color) {
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    int bigestDelta = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xInc = deltaX / (float)bigestDelta;
    float yInc = deltaY / (float)bigestDelta;

    float currentX = x0;
    float currentY = y0;
    for (int i = 0; i <= bigestDelta; i++) {
        drawPixel(round(currentX), round(currentY), color);
        
        currentX += xInc;
        currentY += yInc;
    }
}

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}

void renderColorBuffer(void) {
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int) (windowWidth * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void clearColorBuffer(uint32_t color) {
    for (int y = 0; y < windowHeight; y++){
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void destroyWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}