#include <math.h>

#include "vector.h"

vec3_t vec3RotateZ(vec3_t v, float angle) {
    vec3_t rotatedVector = {
        v.x * cos(angle) - v.y * sin(angle),
        v.x * sin(angle) + v.y * cos(angle),
        v.z
    };

    return rotatedVector;
}