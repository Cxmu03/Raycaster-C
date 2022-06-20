#include "color.h"

#include "util.h"

#define NORMALIZE_RGB_VALUE(c) (map_to((float)(c), 0.f, 255.f, 0.f, 1.f))

color_t create_from_rbg(uint8_t r, uint8_t g, uint8_t b) {
    color_t c = {NORMALIZE_RGB_VALUE(r), NORMALIZE_RGB_VALUE(g), NORMALIZE_RGB_VALUE(b), 1.f};
    return c;
}

color_t color_from_hex(uint32_t hex) {
    color_t c = {NORMALIZE_RGB_VALUE((hex >> 16) & 0xFF),
                 NORMALIZE_RGB_VALUE((hex >> 8) & 0xFF),
                 NORMALIZE_RGB_VALUE(hex & 0xFF),
                 1.f};
    return c;
}