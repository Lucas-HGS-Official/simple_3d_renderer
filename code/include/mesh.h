#ifndef MESH_H
#define MESH_H

#include "vector.h"

#include "triangle.h"

#define NUM_CUBE_VERTICES 8
#define NUM_CUBE_FACES (6 * 2)

extern vec3_t cubeVertices[NUM_CUBE_VERTICES];
extern face_t cubeFaces[NUM_CUBE_FACES];

typedef struct {
    vec3_t* vertices;
    face_t* faces;
    vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

void loadCubeMeshData(void);

#endif