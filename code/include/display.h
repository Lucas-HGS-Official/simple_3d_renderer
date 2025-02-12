#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(void);
void drawGrid(void);
void drawRectFilled(int x, int y, int width, int height, uint32_t color);
void renderColorBuffer(void);
void destroyWindow(void);

#endif