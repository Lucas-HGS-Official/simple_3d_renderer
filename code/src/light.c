#include "light.h"

light_t light = {
    .direction = { 0, 0, 1 }
};

uint32_t lightApplyIntensity(uint32_t originalColor, float percentageFactor) {
    if (percentageFactor < 0) percentageFactor = 0;
    if (percentageFactor > 1) percentageFactor = 1;
    
    uint32_t a = (originalColor & 0xFF000000);
    uint32_t r = (originalColor & 0x00FF0000) * percentageFactor;
    uint32_t g = (originalColor & 0x0000FF00) * percentageFactor;
    uint32_t b = (originalColor & 0x000000FF) * percentageFactor;

    uint32_t newColor = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

    return newColor;
}