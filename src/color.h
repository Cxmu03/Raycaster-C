#ifndef RAYCASTING_COLOR_H
#define RAYCASTING_COLOR_H

#include <stdint.h>

typedef struct {
    float r;
    float g;
    float b;
    float a;
} color_t;

color_t create_from_rbg(uint8_t r, uint8_t g, uint8_t b);
color_t color_from_hex(uint32_t hex);

static const color_t red = {1.f, 0.f, 0.f, 1.f};
static const color_t green = {0.f, 1.f, 0.f, 1.f};
static const color_t blue = {0.f, 0.f, 1.f, 1.f};
static const color_t black = {0.f, 0.f, 0.f, 1.f};
static const color_t white = {1.f, 1.f, 1.f, 1.f};

#endif // RAYCASTING_COLOR_H
