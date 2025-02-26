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

float vec2Length(vec2_t v);

float vec3Length(vec3_t v);
vec3_t vec3RotateX(vec3_t v, float angle);
vec3_t vec3RotateY(vec3_t v, float angle);
vec3_t vec3RotateZ(vec3_t v, float angle);

#endif