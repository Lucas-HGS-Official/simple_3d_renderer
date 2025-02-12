#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;

bool initializeWindow(int windowWidth, int windowHeight, SDL_Window** window, SDL_Renderer** renderer);
void setup(int windowWidth, int windowHeight, SDL_Renderer** renderer);
void processInput(bool* isRunning);
void update(void);
void drawGrid(int windowWidth, int windowHeight);
void drawRectFilled(int x, int y, int width, int height, uint32_t color, int windowWidth);
void renderColorBuffer(int windowWidth, SDL_Renderer** renderer);
void clearColorBuffer(int windowWidth, int windowHeight, uint32_t color);
void render(int windowWidth, int windowHeight, SDL_Renderer** renderer);
void destroyWindow(SDL_Window** window, SDL_Renderer** renderer);

int main(int argc, char const *argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int windowWidth = 800;
    int windowHeight = 600;
    bool isRunning = false;

    isRunning = initializeWindow(windowWidth, windowHeight, &window, &renderer);

    setup(windowWidth, windowHeight, &renderer);

    while (isRunning) {
        processInput(&isRunning);
        update();
        render(windowWidth, windowHeight, &renderer);
    }

    destroyWindow(&window, &renderer);

    return 0;
}

bool initializeWindow(int windowWidth, int windowHeight, SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    *window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if(!*window) {
        fprintf(stderr, "Error creating the SDL Window.\n");

        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if (!*renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");

        return false;
    }

    SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN);

    return true;
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

void clearColorBuffer(int windowWidth, int windowHeight, uint32_t color) {
    for (int y = 0; y < windowHeight; y++){
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void drawGrid(int windowWidth, int windowHeight) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            if (x % 10 == 0 || y % 10 == 0) {
                colorBuffer[(windowWidth * y) + x] = 0xFFFFFFFF;
            }
        }
    }
}

void drawRectFilled(int x, int y, int width, int height, uint32_t color, int windowWidth) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int currentX = x+i;
            int currentY = y+j;
            colorBuffer[(windowWidth * currentY) + currentX] = color;
        }
    }
}

void renderColorBuffer(int windowWidth, SDL_Renderer** renderer) {
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int) (windowWidth * sizeof(uint32_t))
    );

    SDL_RenderCopy(*renderer, colorBufferTexture, NULL, NULL);
}

void render(int windowWidth, int windowHeight, SDL_Renderer** renderer) {
    SDL_SetRenderDrawColor(*renderer, 46, 136, 87, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(*renderer);

    drawGrid(windowWidth, windowHeight);
    drawRectFilled(300, 200, 300, 150, 0xFFFF00FF, windowWidth);

    renderColorBuffer(windowWidth, renderer);
    clearColorBuffer(windowWidth, windowHeight, 0xFFFF0000);

    SDL_RenderPresent(*renderer);
}

void destroyWindow(SDL_Window** window, SDL_Renderer** renderer) {
    free(colorBuffer);
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    *renderer = NULL;
    *window = NULL;
    SDL_Quit();
}