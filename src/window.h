#ifndef RAYCASTING_WINDOW_H
#define RAYCASTING_WINDOW_H

#include <GLFW/glfw3.h>

#include "color.h"
#include "util.h"

typedef enum WINDOW_STYLE {
    STYLE_FULLSCREEN,

} window_style;

typedef struct CURSOR_POSITION {
    double x;
    double y;
} cursor_position;

typedef struct GLFW_CONFIG {
    int profile;
    int majorVersion;
    int minorVersion;
} glfw_config_t;

typedef struct WINDOW_HINT {
    int hint;
    int value;
} window_hint_t;

typedef struct WINDOW_CONFIG {
    size_t width;
    size_t height;
    const char* title;
    GLFWmonitor* monitor;
    GLFWwindow* share;
    float delta_time;
} window_config_t;

typedef struct WINDOW {
    GLFWwindow* glfwWindow;
    window_config_t config;
} window_t;

extern glfw_config_t glfwConfig;

void set_glfw_config(int profile, int majorVersion, int minorVersion);
void set_window_hints(size_t numWindowHints, window_hint_t hint, ...);

void default_framebuffer_callback(window_t* window, int w, int h);

window_t* window_create(window_config_t config, bool fullscreen);
bool window_should_close(window_t* window);
void window_close(window_t* window);
void window_delete(window_t* window);
void window_clear(color_t color);
void window_display(window_t* window);
void window_set_framerate(window_t* window, size_t frameRate);
size_t window_get_framerate(window_t* window);
bool window_key_down(window_t* window, int key);
cursor_position window_get_cursor_pos(window_t* window);
void window_hide_cursor(window_t* window);
void window_show_cursor(window_t* window);

void set_active_window(window_t* window);

#endif // RAYCASTING_WINDOW_H
