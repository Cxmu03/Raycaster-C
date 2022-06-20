#ifndef RAYCASTING_RENDERER_H
#define RAYCASTING_RENDERER_H

#include "color.h"
#include "window.h"

typedef struct RENDERER {
    window_t* window;
    unsigned VAO;
    unsigned VBO;
    unsigned EBO;
} renderer_t;

renderer_t* create_renderer(window_t* w);

void delete_renderer(renderer_t* renderer);

void draw_quad(renderer_t* r, float x, float y, float width, float height, color_t c);

#endif // RAYCASTING_RENDERER_H
