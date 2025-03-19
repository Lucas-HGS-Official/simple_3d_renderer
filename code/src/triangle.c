#include "display.h"

#include "triangle.h"

void intSwapVertex(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float invSlope1 = (float)(x1 - x0) / (y1 - y0);
    float invSlope2 = (float)(x2 - x0) / (y2 - y0);

    float xStart = x0;
    float xEnd = x0;

    for (int y = y0; y <= y2; y++) {
        drawLine(xStart, y, xEnd, y, color);
        xStart += invSlope1;
        xEnd += invSlope2;
    }
}
void fillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float invSlope1 = (float)(x2 - x0) / (y2 - y0);
    float invSlope2 = (float)(x2 - x1) / (y2 - y1);

    float xStart = x2;
    float xEnd = x2;

    for (int y = y2; y >= y0; y--) {
        drawLine(xStart, y, xEnd, y, color);
        xStart -= invSlope1;
        xEnd -= invSlope2;
    }
}

void drawTriangleFilled(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    if (y0 > y1) {
        intSwapVertex(&y0, &y1);
        intSwapVertex(&x0, &x1);
    }
    if (y1 > y2) {
        intSwapVertex(&y1, &y2);
        intSwapVertex(&x1, &x2);
    }
    if (y0 > y1) {
        intSwapVertex(&y0, &y1);
        intSwapVertex(&x0, &x1);
    }

    if (y1 == y2) {
        fillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        fillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {   
        int mY = y1;
        int mX = ((float)((x2-x0) * (y1-y0)) / (float)(y2-y0)) + x0;
        
        fillFlatBottomTriangle(x0, y0, x1, y1, mX, mY, color);
        fillFlatTopTriangle(x1, y1, mX, mY, x2, y2, color);
    }
}

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}