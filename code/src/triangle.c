#include "triangle.h"

void intSwapVertex(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int mX, int mY, uint32_t color) {

}
fillFlatTopTriangle(int x1, int y1, int mX, int mY, int x2, int y2, uint32_t color) {

}

void drawTriangleFilled(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    if (y0 > y1) {
        swapVertex(&y0, &y1);
        swapVertex(&x0, &x1);
    }
    if (y1 > y2) {
        swapVertex(&y1, &y2);
        swapVertex(&x1, &x2);
    }
    if (y0 > y1) {
        swapVertex(&y0, &y1);
        swapVertex(&x0, &x1);
    }

    int mY = y1;
    int mX = ((float)((x2-x0) * (y1-y0)) / (float)(y2-y0)) + x0;

    fillFlatBottomTriangle(x0, y0, x1, y1, mX, mY, color);
    fillFlatTopTriangle(x1, y1, mX, mY, x2, y2, color);
}