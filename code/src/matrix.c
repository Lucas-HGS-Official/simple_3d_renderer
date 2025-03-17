#include <math.h>

#include "matrix.h"

mat4_t mat4Identity() {
    mat4_t m = {{
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    }};

    return m;
}

mat4_t mat4MakeScale(float sx, float sy, float sz) {
    mat4_t m = mat4Identity();
    
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;

    return m;
}

mat4_t mat4MultMat4(mat4_t m1, mat4_t m2) {
    mat4_t result;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            result.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
        }
    }

    return result;
}

vec4_t mat4MultVec4(mat4_t m, vec4_t v) {
    vec4_t result;

    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

    return result;
}

mat4_t mat4MakeTranslation(float tx, float ty, float tz) {
    mat4_t m = mat4Identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;

    return m;
}

mat4_t mat4MakeRotationX(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    mat4_t m = mat4Identity();
    m.m[1][1] = c;
    m.m[1][2] = -s;
    m.m[2][1] = s;
    m.m[2][2] = c;

    return m;
}

mat4_t mat4MakeRotationY(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    mat4_t m = mat4Identity();
    m.m[0][0] = c;
    m.m[0][2] = s;
    m.m[2][0] = -s;
    m.m[2][2] = c;
    
    return m;
}

mat4_t mat4MakeRotationZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    mat4_t m = mat4Identity();
    m.m[0][0] = c;
    m.m[0][1] = -s;
    m.m[1][0] = s;
    m.m[1][1] = c;
    
    return m;
}


mat4_t mat4MakePerspective(float fov, float aspect, float znear, float zfar) {
    mat4_t m = {{{ 0 }}};

    m.m[0][0] = aspect * (1/tan(fov/2));
    m.m[1][1] = 1 / tan(fov/2);
    m.m[2][2] = zfar / (zfar - znear);
    m.m[2][3] = (-zfar * znear) / (zfar - znear);
    m.m[3][2] = 1.0;

    return m;
}

vec4_t mat4MultVec4Project(mat4_t matProj, vec4_t v) {
    vec4_t result = mat4MultVec4(matProj, v);

    if (result.w != 0.0) {
        result.x /= result.w;
        result.y /= result.w;
        result.z /= result.w;
    }

    return result;
}