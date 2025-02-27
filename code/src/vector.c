#include <math.h>

#include "vector.h"


float vec2Length(vec2_t v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

vec2_t vec2Addition(vec2_t v1, vec2_t v2) {
    return (vec2_t) { v1.x + v2.x, v1.y + v2.y };
}


float vec3Length(vec3_t v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec3_t vec3Addition(vec3_t v1, vec3_t v2){
    return (vec3_t) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vec3_t vec3RotateX(vec3_t v, float angle) {
    vec3_t rotatedVector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };

    return rotatedVector;
}

vec3_t vec3RotateY(vec3_t v, float angle) {
    vec3_t rotatedVector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };

    return rotatedVector;
}

vec3_t vec3RotateZ(vec3_t v, float angle) {
    vec3_t rotatedVector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };

    return rotatedVector;
}