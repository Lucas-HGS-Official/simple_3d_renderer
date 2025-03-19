#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int windowWidth;
extern int windowHeight;

extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;

bool initializeWindow(void);
void drawPixel(int x, int y, uint32_t color);
void drawGrid(void);
void drawDottedGrid(void);
void drawRectFilled(int x, int y, int width, int height, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void renderColorBuffer(void);
void clearColorBuffer(uint32_t color);
void destroyWindow(void);

#endif