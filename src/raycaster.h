#ifndef RAYCASTING_RAYCASTER_H
#define RAYCASTING_RAYCASTER_H

#include <omp.h>
#include <stdint.h>

#include "map.h"
#include "player.h"
#include "renderer.h"
#include "shaders.h"
#include "window.h"

typedef struct RAYCASTING_CONFIG {
    size_t numColumns;
    float fov; // in radians
    float stepSize;
} raycasting_config_t;

typedef struct GL_CONTEXT {
    window_t* window;
    renderer_t* renderer;
    shader_program_t* program;
} gl_context_t;

typedef struct RAYCASTER {
    raycasting_config_t* config;
    player_t* player;
    gl_context_t* glContext;
    map_t* map;
} raycaster_t;

raycaster_t* create_raycaster(raycasting_config_t* config, player_t* playerState, gl_context_t* context, map_t* map);
void set_active_raycaster(raycaster_t* raycaster);

void run_raycaster(raycaster_t* raycaster);
void benchmark_raycaster(raycaster_t* raycaster);

#endif // RAYCASTING_RAYCASTER_H
