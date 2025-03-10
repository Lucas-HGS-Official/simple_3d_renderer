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

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4_t;

float vec2Length(vec2_t v);
vec2_t vec2Addition(vec2_t v1, vec2_t v2);
vec2_t vec2Subtraction(vec2_t v1, vec2_t v2);
vec2_t vec2Scalling(vec2_t v, float factor);
vec2_t vec2Division(vec2_t v, float factor);
float vec2DotProduct(vec2_t v1, vec2_t v2);
void vec2Normalize(vec2_t* v);

float vec3Length(vec3_t v);
vec3_t vec3Addition(vec3_t v1, vec3_t v2);
vec3_t vec3Subtraction(vec3_t v1, vec3_t v2);
vec3_t vec3Scalling(vec3_t v, float factor);
vec3_t vec3Division(vec3_t v, float factor);
vec3_t vec3CrossProduct(vec3_t v1, vec3_t v2);
float vec3DotProduct(vec3_t v1, vec3_t v2);
void vec3Normalize(vec3_t* v);
vec3_t vec3RotateX(vec3_t v, float angle);
vec3_t vec3RotateY(vec3_t v, float angle);
vec3_t vec3RotateZ(vec3_t v, float angle);

vec4_t vec4FromVec3(vec3_t v);
vec3_t vec3FromVec4(vec4_t v);

#endif