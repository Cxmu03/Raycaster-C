#include "window.h"

#include <glad/glad.h>
#include <malloc.h>
#include <stdarg.h>

#include "log.h"
#include "util.h"

glfw_config_t glfwConfig;
static bool glfwIsInitialized = false;
static bool gladIsInitialized = false;

void set_glfw_config(int profile, int majorVersion, int minorVersion) {
    glfwConfig.profile = profile;
    glfwConfig.majorVersion = majorVersion;
    glfwConfig.minorVersion = minorVersion;
}

static void internal_default_framebuffer_callback(GLFWwindow* glfwWindow, int w, int h) {
    glViewport(0, 0, w, h);
    window_t* activeWindow = glfwGetWindowUserPointer(glfwWindow);
    activeWindow->config.width = w;
    activeWindow->config.height = h;
}

void default_framebuffer_callback(window_t* window, int w, int h) {
    internal_default_framebuffer_callback(window->glfwWindow, w, h);
}

window_t* window_create(window_config_t config, bool fullscreen) {
    glfwWindowHint(GLFW_OPENGL_PROFILE, glfwConfig.profile);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwConfig.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwConfig.minorVersion);
    if(!glfwIsInitialized && !glfwInit()) {
        BEEP_BEEP_FEHLER_ERKANNT("Failed to initialize GLFW\n");
        glfwIsInitialized = true;
    }

    window_t* window = malloc(sizeof(window_t));
    GLFWwindow* glfwWindow = glfwCreateWindow(config.width, config.height, config.title, fullscreen ? glfwGetPrimaryMonitor() : config.monitor, config.share);
    window->config.width = config.width;
    window->config.height = config.height;
    window->glfwWindow = glfwWindow;
    glfwSetFramebufferSizeCallback(glfwWindow, internal_default_framebuffer_callback);
    glfwSetWindowUserPointer(glfwWindow, window);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* primaryVidMode = glfwGetVideoMode(monitor);
    window->config.delta_time = 1.f / (float)primaryVidMode->refreshRate;

    glfwMakeContextCurrent(window->glfwWindow);
    if(!gladIsInitialized && !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        BEEP_BEEP_FEHLER_ERKANNT("Failed to load glad\n");
        gladIsInitialized = true;
    }

    return window;
}

void window_set_framerate(window_t* window, size_t frameRate) {
    window->config.delta_time = 1.f / (float)frameRate;
}

size_t window_get_framerate(window_t* window) {
    return (size_t)(1.f / window->config.delta_time);
}

bool window_should_close(window_t* window) {
    return glfwWindowShouldClose(window->glfwWindow);
}

void window_delete(window_t* window) {
    glfwDestroyWindow(window->glfwWindow);
    free(window);
}

void window_clear(color_t color) {
    glClearColor(color.r, color.g, color.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_display(window_t* window) {
    glfwSwapBuffers(window->glfwWindow);
}

void set_active_window(window_t* window) {
    glfwSetWindowUserPointer(window->glfwWindow, window);
    glfwMakeContextCurrent(window->glfwWindow);
    glViewport(0, 0, window->config.width, window->config.height);
}

bool window_key_down(window_t* window, int key) {
    return glfwGetKey(window->glfwWindow, key) == GLFW_PRESS;
}

void set_window_hints(size_t numWindowHints, window_hint_t hint, ...) {
    va_list args;
    va_start(args, hint);
    for(int i = 0; i < numWindowHints; i++) {
        glfwWindowHint(hint.hint, hint.value);
        va_arg(args, window_t);
    }
}

void window_show_cursor(window_t* window) {
    glfwSetInputMode(window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void window_hide_cursor(window_t* window) {
    glfwSetInputMode(window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

cursor_position window_get_cursor_pos(window_t* window) {
    double cursorX, cursorY;
    glfwGetCursorPos(window->glfwWindow, &cursorX, &cursorY);
    return (cursor_position) {cursorX, cursorY};
}

void window_close(window_t* window) {
    glfwSetWindowShouldClose(window->glfwWindow, GLFW_TRUE);
}