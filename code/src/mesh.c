#include <stdio.h>
#include <string.h>

#include "array.h"

#include "mesh.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = { 0, 0, 0 }
};

vec3_t cubeVertices[NUM_CUBE_VERTICES] = {
    { -1, -1, -1 }, // 1
    { -1,  1, -1 }, // 2
    {  1,  1, -1 }, // 3
    {  1, -1, -1 }, // 4
    {  1,  1,  1 }, // 5
    {  1, -1,  1 }, // 6
    { -1,  1,  1 }, // 7
    { -1, -1,  1 }  // 8
};

face_t cubeFaces[NUM_CUBE_FACES] = {
    // front
    {1, 2, 3},
    {1, 3, 4},
    // right
    {4, 3, 5},
    {4, 5, 6},
    // back
    {6, 5, 7},
    {6, 7, 8},
    // left
    {8, 7, 2},
    {8, 2, 1},
    // top
    {2, 7, 5},
    {2, 5, 3},
    // bottom
    {6, 8, 1},
    {6, 1, 4}
};

void loadCubeMeshData(void) {
    for (int i = 0; i < NUM_CUBE_VERTICES; i++) {
        vec3_t cubeVertex = cubeVertices[i];
        array_push(mesh.vertices, cubeVertex);
    }

    for (int i = 0; i < NUM_CUBE_FACES; i++) {
        face_t cubeFace = cubeFaces[i];
        array_push(mesh.faces, cubeFace);
    }
}

void loadObjFileData(char* filepath) {
    FILE* file = NULL;
    file = fopen(filepath, "r");

    char line[512];

    while (fgets(line, 512, file)) {
        if (strncmp(line, "v ", 2) == 0) {
            vec3_t vertex;
            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            array_push(mesh.vertices, vertex);
        }
        if (strncmp(line, "f ", 2) == 0) {
            int vertexIndices[3];
            int textureIndices[3];
            int normalsIndices[3];
            sscanf(
                line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vertexIndices[0], &textureIndices[0], &normalsIndices[0],
                &vertexIndices[1], &textureIndices[1], &normalsIndices[1],
                &vertexIndices[2], &textureIndices[2], &normalsIndices[2]
            );

            face_t face = {
                .a = vertexIndices[0],
                .b = vertexIndices[1],
                .c = vertexIndices[2]
            };

            array_push(mesh.faces, face);
        }
    }
}