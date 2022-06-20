#include <GLFW/glfw3.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>

#include "player.h"

#define WARP_CURSOR_WHEN(condition, var, pos) if(cond) { (var) = (pos) }

static void move_player_in_direction(player_t* player, movement_direction_t direction, float delta_time) {
    player->x += 4.f * cosf(player->angle + deg_to_rad((float)direction)) * delta_time;
    player->y -= 4.f * sinf(player->angle + deg_to_rad((float)direction)) * delta_time;
}

static inline bool in_movement_keys(int key) {
    return key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D;
}

static void default_input_handler(player_t* player, window_t* window) {
    if(window_key_down(window, GLFW_KEY_RIGHT)) { player->angle -= 0.03f; }

    if(window_key_down(window, GLFW_KEY_LEFT)) { player->angle += 0.03f; }

    if(window_key_down(window, GLFW_KEY_W)) {
        move_player_in_direction(player, DIRECTION_UP, window->config.delta_time);
    }
    if(window_key_down(window, GLFW_KEY_A)) {
        move_player_in_direction(player, DIRECTION_LEFT, window->config.delta_time);
    }
    if(window_key_down(window, GLFW_KEY_S)) {
        move_player_in_direction(player, DIRECTION_DOWN, window->config.delta_time);
    }
    if(window_key_down(window, GLFW_KEY_D)) {
        move_player_in_direction(player, DIRECTION_RIGHT, window->config.delta_time);
    }
    double x, y;
    glfwGetCursorPos(window->glfwWindow, &x, &y);
}

static void default_mouse_handler(player_t* player, window_t* window, cursor_position lastCursorPos) {

}

void update_player(player_t* player, float deltaTime) {
}

player_t* create_player(float x, float y, float angle) {
    player_t* player = malloc(sizeof(player));
    player->x = x;
    player->y = y;
    player->z = 0;
    player->angle = angle;
    player->player_input_handler = default_input_handler;
    player->player_mouse_handler = default_mouse_handler;
    return player;
}