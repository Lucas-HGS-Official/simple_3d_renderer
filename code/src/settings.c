#include "settings.h"

static int render_method = 0;
static int cull_method = 0;

void set_render_method(int method) {
    render_method = method;
}

void set_cull_method(int method) {
    cull_method = method;
}

bool is_cull_backface(void) {
    return cull_method == CULL_BACKFACE;
}

bool should_render_textured_triangles(void) {
    return (
        render_method == RENDER_TEXTURED ||
        render_method == RENDER_TEXTURED_WIRE
    );
}

bool should_render_wireframe(void) {
    return (
        render_method == RENDER_WIRE ||
        render_method == RENDER_WIRE_VERTEX ||
        render_method == RENDER_FILL_TRIANGLE_WIRE ||
        render_method == RENDER_TEXTURED_WIRE
    );
}

bool should_render_filled_triangles(void) {
    return (
        render_method == RENDER_FILL_TRIANGLE ||
        render_method == RENDER_FILL_TRIANGLE_WIRE 
    );
}

bool should_render_wire_vertex(void) {
    return (
        render_method == RENDER_WIRE_VERTEX
    );
}