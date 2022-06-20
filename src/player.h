#ifndef RAYCASTING_PLAYER_H
#define RAYCASTING_PLAYER_H

#include "util.h"
#include "window.h"

typedef enum { DIRECTION_UP = 0, DIRECTION_LEFT = 90, DIRECTION_DOWN = 180, DIRECTION_RIGHT = 270} movement_direction_t;

struct PLAYER;
typedef void (*input_handler)(struct PLAYER* player, window_t* window);
typedef void (*mouse_handler)(struct PLAYER* player, window_t* window, cursor_position lastCursorPos);

typedef struct PLAYER {
    float x;
    float y;
    float z;
    float angle;
    bool rotating;
    input_handler player_input_handler;
    mouse_handler player_mouse_handler;
} player_t;

player_t* create_player(float x, float y, float angle);
void update_player(player_t* player, float deltaTime);

#endif // RAYCASTING_PLAYER_H
