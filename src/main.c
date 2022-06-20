#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <malloc.h>
#include <stdio.h>

#include "log.h"
#include "raycaster.h"
#include "renderer.h"
#include "shaders.h"
#include "util.h"

int main() {
    set_glfw_config(GLFW_OPENGL_CORE_PROFILE, 3, 3);
    window_t* window = window_create((window_config_t){500, 500, "Raycaster", NULL, NULL}, false);
    window_set_framerate(window, 60);
    //window_hide_cursor(window);

    renderer_t* renderer = create_renderer(window);

    shader_information_t vertexShaderInformation = {GL_VERTEX_SHADER, "../shaders/shader.vert"};
    shader_information_t fragmentShaderInformation = {GL_FRAGMENT_SHADER, "../shaders/shader.frag"};
    shader_program_t* program = create_program(2, vertexShaderInformation, fragmentShaderInformation);
    delete_attached_shaders(program);
    use_program(program);
    INFO("Created shaders and shader program\n");

    gl_context_t context = {window, renderer, program};

    uint8_t mapData[24 * 24]=
        {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
            1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
            1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
        };

    map_t map = {.data = mapData, .width = 24, .height = 24};

    raycasting_config_t raycasterConfig = {.numColumns = 1920, .stepSize = 0.05, .fov = PI_HALVES};

    player_t* player = create_player(3.f, 3.f, PI_HALVES);

    raycaster_t* raycaster = create_raycaster(&raycasterConfig, player, &context, &map);
    printf("x: %d, y: %d", raycaster->player->x, raycaster->player->y);
    // raycaster->glContext = &context;

    run_raycaster(raycaster);

    window_delete(window);
    free(program);
}