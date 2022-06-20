#ifndef RAYCASTING_MAP_H
#define RAYCASTING_MAP_H

#include <stdint.h>

#include "color.h"

typedef struct TILE {
    enum { TEXTURE_FLAT_COLOR = 0x00, TEXTURE_TEXTURED } texture_type;

    union {
        color_t color;
        const char* texturePath;
    };
} tile_t;

typedef struct MAP {
    uint8_t* data;
    size_t width;
    size_t height;
} map_t;

typedef enum TILE_TYPE {
    NONE = 0x00,
    WALL,
    WALL_GREEN,
    WALL_PURPLE,
    OOB // out of bounds
} tile_type;

static const char* tile_type_strings[] = {[NONE] = "WALL_TYPE_NONE",
                                          [WALL] = "WALL_TYPE_WALL",
                                          [WALL_GREEN] = "WALL_TYPE_WALL_GREEN",
                                          [WALL_PURPLE] = "WALL_TYPE_WALL_PURPLE",
                                          [OOB] = "WALL_TYPE_OUT_OF_BOUNDS"};

static color_t tile_colors[] = {
    [WALL] = {.r = 0.f, .g = 0.f, .b = 1.f, .a = 1.f},
    [WALL_GREEN] = {.r = 0.f, .g = 1.f, .b = 0.f, .a = 1.f},
    [WALL_PURPLE] = {.r = 1.f, .g = 0.f, .b = 1.f, .a = 1.f},
    [OOB] = {.r = 1.f, .g = 0.f, .b = 0.f, .a = 1.f},
};

map_t* read_map(const char* filename);
uint8_t get_map_at(map_t* map, size_t x, size_t y);

#endif // RAYCASTING_MAP_H
