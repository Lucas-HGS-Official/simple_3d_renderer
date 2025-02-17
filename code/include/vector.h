#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
}vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;


vec3_t vec3RotateZ(vec3_t v, float angle);

#endif