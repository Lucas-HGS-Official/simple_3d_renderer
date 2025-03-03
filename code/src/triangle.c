#include "triangle.h"

void intSwapVertex(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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
}