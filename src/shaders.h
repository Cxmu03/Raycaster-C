#ifndef RAYCASTING_SHADERS_H
#define RAYCASTING_SHADERS_H

#include <glad/glad.h>

#include "util.h"

typedef GLuint shader_id;
typedef GLuint program_id;
typedef GLenum shader_type;

typedef struct shader_information_t {
    shader_type shaderType;
    const char* shaderPath;
} shader_information_t;

typedef struct shader_t {
    shader_id id;
    shader_type shaderType;
} shader_t;

typedef struct shader_program_t {
    program_id id;
    shader_t** attachedShaders;
    size_t attachedShadersSize;
    bool active;
} shader_program_t;

struct shader_log;

struct shader_log* get_shader_status();

shader_t* create_shader(GLenum type, const char* path);
void delete_shader(shader_t* shader);
shader_t* create_vertex_shader(const char* path);
shader_t* create_fragment_shader(const char* path);

shader_program_t* create_empty_program();
shader_program_t* create_program(size_t numShaders, shader_information_t shaderInfo, ...);
void use_program(shader_program_t* program);
void attach_shaders(shader_program_t* program, size_t numShaders, shader_t* shader, ...);
void delete_attached_shaders(shader_program_t* program);
void set_vertex_attribute();
void compile_program(shader_program_t* program);

#endif // RAYCASTING_SHADERS_H
