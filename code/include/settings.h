#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

enum cull_method {
    CULL_NONE,
    CULL_BACKFACE
};

enum render_method {
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE,
    RENDER_TEXTURED,
    RENDER_TEXTURED_WIRE
};

void set_render_method(int method);
void set_cull_method(int method);
bool is_cull_backface(void);

bool should_render_textured_triangles(void);
bool should_render_wireframe(void);
bool should_render_filled_triangles(void);
bool should_render_wire_vertex(void);

#endif