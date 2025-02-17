#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int windowWidth;
extern int windowHeight;

extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;

bool initializeWindow(void);
void drawPixel(int x, int y, uint32_t color);
void drawGrid(void);
void drawRectFilled(int x, int y, int width, int height, uint32_t color);
void renderColorBuffer(void);
void clearColorBuffer(uint32_t color);
void destroyWindow(void);

#endif