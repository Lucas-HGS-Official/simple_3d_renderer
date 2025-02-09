#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Renderer* renderer = NULL;

uint32_t* colorBuffer = NULL;

SDL_Texture* colorBufferTexture = NULL;

bool initialize_window(int windowWidth, int windowHeight, SDL_Window** window);
void setup(int windowWidth, int windowHeight);
void process_input(bool* isRunning);
void update(void);
void render_color_buffer(int windowWidth);
void clearColorBuffer(int windowWidth, int windowHeight, uint32_t color);
void render(int windowWidth, int windowHeight);
void destroy_window(SDL_Window** window);

int main(int argc, char const *argv[]) {
    SDL_Window* window = NULL;

    int windowWidth = 800;
    int windowHeight = 600;
    bool isRunning = false;

    isRunning = initialize_window(windowWidth, windowHeight, &window);

    setup(windowWidth, windowHeight);

    while (isRunning) {
        process_input(&isRunning);
        update();
        render(windowWidth, windowHeight);
    }

    destroy_window(&window);

    return 0;
}

bool initialize_window(int windowWidth, int windowHeight, SDL_Window** window) {
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

    renderer = SDL_CreateRenderer(*window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");

        return false;
    }

    SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void setup(int windowWidth, int windowHeight) {
    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);

    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );
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

void clearColorBuffer(int windowWidth, int windowHeight, uint32_t color) {
    for (int y = 0; y < windowHeight; y++){
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void render_color_buffer(int windowWidth) {
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int) (windowWidth * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void render(int windowWidth, int windowHeight) {
    SDL_SetRenderDrawColor(renderer, 46, 136, 87, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    render_color_buffer(windowWidth);
    clearColorBuffer(windowWidth, windowHeight, 0xFFFF00);

    SDL_RenderPresent(renderer);
}

void destroy_window(SDL_Window** window) {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}