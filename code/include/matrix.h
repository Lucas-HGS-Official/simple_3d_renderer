#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
    float m[4][4];
} mat4_t;

mat4_t mat4Identity(void);
mat4_t mat4MakeScale(float sx, float sy, float sz);
vec4_t mat4MultVec4(mat4_t m, vec4_t v);

#endif