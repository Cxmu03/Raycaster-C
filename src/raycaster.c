#include "raycaster.h"

#include <GLFW/glfw3.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <omp.h>

typedef struct {
    float distance;
    tile_type type;
} raycasting_result_t;

static raycaster_t* active_raycaster;

void key_callback(GLFWwindow*, int, int, int, int);

raycaster_t* create_raycaster(raycasting_config_t* config, player_t* playerState, gl_context_t* context, map_t* map) {
    raycaster_t* raycaster = calloc(1, sizeof(raycaster_t));
    raycaster->config = config;
    raycaster->glContext = context;
    raycaster->player = playerState;
    raycaster->map = map;

    active_raycaster = raycaster;
    glfwSetKeyCallback(context->window->glfwWindow, key_callback);

    return raycaster;
}

void set_actice_raycaster(raycaster_t* raycaster) {
    active_raycaster = raycaster;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

static raycasting_result_t* cast_rays(raycaster_t* raycaster) {
    raycasting_config_t* raycasterConfig = raycaster->config;
    player_t* player = raycaster->player;
    map_t* map = raycaster->map;

    raycasting_result_t* results = calloc(raycasterConfig->numColumns, sizeof(raycasting_result_t));

#pragma omp parallel for schedule(static)
    for(int i = 0; i < raycasterConfig->numColumns; i++) {
        bool hitWall = false;
        tile_type type = 0;

        float rayX = player->x;
        float rayY = player->y;
        float distance = 0.f;
        const float angle = (player->angle + (raycasterConfig->fov / 2.f)) -
                            ((raycasterConfig->fov / (float)raycasterConfig->numColumns) * (float)i);

        int rayTileX, rayTileY;

        while(!hitWall) {
            float rayDeltaX = cosf(angle) * raycasterConfig->stepSize;
            float rayDeltaY = sinf(angle) * raycasterConfig->stepSize;

            rayX += rayDeltaX;
            rayY -= rayDeltaY;

            distance += raycasterConfig->stepSize;

            // printf("Ray Pos: {%f, %f}", rayX, rayY);

            rayTileX = (int)rayX;
            rayTileY = (int)rayY;

            if(rayX < 0 || rayX >= (float)map->width || rayY < 0 || (rayY >= (float)map->height)) {
                type = OOB;
                break;
            }

            type = get_map_at(map, rayTileX, rayTileY);

            if(type != NONE) { hitWall = true; }
        }

        // printf("Type of tile is %d\n", type);
        results[i].distance = distance;
        results[i].type = type;
    }

    return results;
}

static void draw_results(raycaster_t* raycaster, raycasting_result_t* results) {
    for(int i = 0; i < raycaster->config->numColumns; i++) {
        color_t tileColor = tile_colors[results[i].type];

        const float wallWidth =
            (float)raycaster->glContext->window->config.width / (float)raycaster->config->numColumns;
        const float wallHeight = raycaster->glContext->window->config.height / results[i].distance;
        const float wallXStart = (float)i * wallWidth;
        const float wallYStart = ((float)raycaster->glContext->window->config.height - wallHeight) / 2.f + raycaster->player->z;

        draw_quad(raycaster->glContext->renderer, wallXStart, wallYStart, wallWidth, wallHeight, tileColor);
    }
}

void run_raycaster(raycaster_t* raycaster) {
    while(!window_should_close(raycaster->glContext->window)) {
        clock_t c1 = clock();
        window_clear(white);

        raycaster->player->player_input_handler(raycaster->player, raycaster->glContext->window);
        //update_player(raycaster->player, raycaster->glContext->window->config.delta_time);

        raycasting_result_t* results = cast_rays(raycaster);
        draw_results(raycaster, results);

        window_display(raycaster->glContext->window);
        float elapsedSeconds = (((float)(clock() - c1)) / CLOCKS_PER_SEC);
        raycaster->glContext->window->config.delta_time = elapsedSeconds;
        glfwPollEvents();
    }
}