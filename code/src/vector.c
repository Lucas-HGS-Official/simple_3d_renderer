#include <math.h>

#include "vector.h"


float vec2Length(vec2_t v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

vec2_t vec2Addition(vec2_t v1, vec2_t v2) {
    return (vec2_t) { v1.x + v2.x, v1.y + v2.y };
}

vec2_t vec2Subtraction(vec2_t v1, vec2_t v2) {
    return (vec2_t) { v1.x - v2.x, v1.y - v2.y };
}

vec2_t vec2Scalling(vec2_t v, float factor) {
    return (vec2_t) { v.x*factor, v.y*factor };
}

vec2_t vec2Division(vec2_t v, float factor) {
    return (vec2_t) { v.x/factor, v.y/factor };
}

float vec2DotProduct(vec2_t v1, vec2_t v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

void vec2Normalize(vec2_t* v) {
    vec2Division(*v, vec2Length(*v));
}


float vec3Length(vec3_t v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec3_t vec3Addition(vec3_t v1, vec3_t v2){
    return (vec3_t) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vec3_t vec3Subtraction(vec3_t v1, vec3_t v2) {
    return (vec3_t) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

vec3_t vec3Scalling(vec3_t v, float factor) {
    return (vec3_t) { v.x*factor, v.y*factor, v.z*factor };
}

vec3_t vec3Division(vec3_t v, float factor) {
    return (vec3_t) { v.x/factor, v.y/factor, v.z/factor };
}

vec3_t vec3CrossProduct(vec3_t v1, vec3_t v2) {
    return (vec3_t) {
        .x = v1.y * v2.z - v1.z * v2.y,
        .y = v1.z * v2.x - v1.x * v2.z,
        .z = v1.x * v2.y - v1.y * v2.x
    };
}

float vec3DotProduct(vec3_t v1, vec3_t v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void vec3Normalize(vec3_t* v) {
    vec3Division(*v, vec3Length(*v));
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