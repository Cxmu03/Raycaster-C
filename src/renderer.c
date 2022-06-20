#include "renderer.h"

#include <glad/glad.h>
#include <malloc.h>

#include "util.h"

#define MAP_VERTEX(c, name) map_to((float)(c), 0.f, (float)name, -1.f, 1.f)
#define MAP_TO_WIDTH(x)     map_to((float)(x), 0.f, (float)windowWidth, -1.f, 1.f)
#define MAP_TO_HEIGHT(y)    map_to((float)(y), 0.f, (float)windowHeight, 1.f, -1.f)

static unsigned quadIndices[] = {0, 1, 2, 2, 3, 0};

renderer_t* create_renderer(window_t* w) {
    renderer_t* r = malloc(sizeof(renderer_t));
    r->window = w;
    glGenBuffers(1, &r->VBO);
    glGenBuffers(1, &r->EBO);
    glGenVertexArrays(1, &r->VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    return r;
}

void delete_renderer(renderer_t* r) {
    glDeleteBuffers(1, &r->VBO);
    glDeleteBuffers(1, &r->EBO);
    glDeleteBuffers(1, &r->VAO);
    free(r);
}

typedef struct {
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;
} quad_vertices;

static quad_vertices
calculate_quad_vertices(float x, float y, float width, float height, unsigned windowWidth, unsigned windowHeight) {
    float x1 = MAP_TO_WIDTH(x);
    float y1 = MAP_TO_HEIGHT(y);
    float x2 = MAP_TO_WIDTH(x + width);
    float y2 = MAP_TO_HEIGHT(y + height);

    quad_vertices vertices = {x1, y1, x2, y1, x2, y2, x1, y2};
    return vertices;
}

void draw_quad_from_vertices(renderer_t* r, float vertices[]) {
    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBindVertexArray(r->VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, quadIndices);
}

void draw_quad(renderer_t* r, float x, float y, float width, float height, color_t c) {
    quad_vertices v = calculate_quad_vertices(x, y, width, height, r->window->config.width, r->window->config.height);
    float vertices[] = {v.x1, v.y1, 0.f, c.r, c.g, c.b, v.x2, v.y2, 0.f, c.r, c.g, c.b,
                        v.x3, v.y3, 0.f, c.r, c.g, c.b, v.x4, v.y4, 0.f, c.r, c.g, c.b};

    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBindVertexArray(r->VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, quadIndices);
}