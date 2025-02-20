#ifndef MESH_H
#define MESH_H

#include "vector.h"

#include "triangle.h"

#define NUM_MESH_VERTICES 8
#define NUM_MESH_FACES (6 * 2)

extern vec3_t meshVertices[NUM_MESH_VERTICES];
extern face_t meshFaces[NUM_MESH_FACES];

#endif