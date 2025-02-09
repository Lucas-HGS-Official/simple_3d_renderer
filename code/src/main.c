#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* colorBuffer = NULL;

SDL_Texture* colorBufferTexture = NULL;

int windowWidth = 800;
int windowHeight = 600;

bool initialize_window();
void setup(void);
void process_input(bool* isRunning);
void update(void);
void render_color_buffer(void);
void clearColorBuffer(uint32_t color);
void render(void);
void destroy_window(void);

int main(int argc, char const *argv[]) {
    bool isRunning = false;

    isRunning = initialize_window();

    setup();

    while (isRunning) {
        process_input(&isRunning);
        update();
        render();
    }

    destroy_window();

    return 0;
}

bool initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

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

    return true;
}

void setup() {
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

void clearColorBuffer(uint32_t color) {
    for (int y = 0; y < windowHeight; y++){
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void render_color_buffer() {
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int) (windowWidth * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 46, 136, 87, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    render_color_buffer();
    clearColorBuffer(0xFFFF00);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}