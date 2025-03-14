#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
    float m[4][4];
} mat4_t;

mat4_t mat4Identity(void);
mat4_t mat4MakeScale(float sx, float sy, float sz);
mat4_t mat4MultMat4(mat4_t m1, mat4_t m2);
vec4_t mat4MultVec4(mat4_t m, vec4_t v);
mat4_t mat4MakeTranslation(float tx, float ty, float tz);
mat4_t mat4MakeRotationX(float angle);
mat4_t mat4MakeRotationY(float angle);
mat4_t mat4MakeRotationZ(float angle);

#endif