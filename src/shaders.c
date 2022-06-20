#include "shaders.h"

#include <glad/glad.h>
#include <stdarg.h>

#include "file_reader.h"
#include "log.h"

struct shader_log {
    GLuint statusType;
    char infoLog[512];
    int success;
};

static struct shader_log* log;

struct shader_log* get_shader_status() {
    return log;
}

shader_t* create_shader(shader_type type, const char* path) {
    char infoLog[512];
    bool success;
    shader_t* shader = malloc(sizeof(shader_t));
    shader->shaderType = type;
    shader->id = glCreateShader(type);
    char* shaderSource;
    size_t shaderSourceSize;
    read_file(path, &shaderSource, &shaderSourceSize);
    glShaderSource(shader->id, 1, (const GLchar* const*)&shaderSource, NULL);
    glCompileShader(shader->id);
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, (int*)&success);
    if(!success) {
        glGetShaderInfoLog(shader->id, 512, NULL, infoLog);
        BEEP_BEEP_FEHLER_ERKANNT("Failed to compile fragment shader\n%s\n", infoLog);
    }
    free(shaderSource);
    return shader;
}

shader_t* create_vertex_shader(const char* path) {
    return create_shader(GL_VERTEX_SHADER, path);
}

shader_t* create_fragment_shader(const char* path) {
    return create_shader(GL_FRAGMENT_SHADER, path);
}

void delete_shader(shader_t* shader) {
    glDeleteShader(shader->id);
    free(shader);
}

void delete_attached_shaders(shader_program_t* program) {
    for(int i = 0; i < program->attachedShadersSize; i++) {
        glDeleteShader(program->attachedShaders[i]->id);
        free(program->attachedShaders[i]);
    }
    free(program->attachedShaders);
}

void attach_shaders(shader_program_t* program, size_t numShaders, shader_t* shader, ...) {
    if(program->attachedShaders != NULL) { free(program->attachedShaders); }
    program->attachedShaders = malloc(numShaders * sizeof(shader_t*));
    program->attachedShadersSize = numShaders;
    va_list args;
    va_start(args, shader);
    for(int i = 0; i < numShaders; i++) {
        glAttachShader(program->id, shader->id);
        program->attachedShaders[i] = shader;

        shader = va_arg(args, shader_t*);
    }
    va_end(args);
}

void compile_program(shader_program_t* program) {
    char infoLog[512];
    bool success;
    glLinkProgram(program->id);
    glGetProgramiv(program->id, GL_LINK_STATUS, (int*)&success);
    if(!success) {
        glGetProgramInfoLog(program->id, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Failed to link shader program\n%s\n", infoLog);
    }
}

void use_program(shader_program_t* program) {
    glUseProgram(program->id);
    program->active = true;
}

shader_program_t* create_empty_program() {
    shader_program_t* program = malloc(sizeof(shader_program_t));
    program_id id = glCreateProgram();
    program->id = id;
    program->active = false;
    program->attachedShaders = NULL;
    return program;
}

shader_program_t* create_program(size_t numShaders, shader_information_t shaderInfo, ...) {
    shader_program_t* program = create_empty_program();
    shader_t** shaders = malloc(numShaders * sizeof(shader_t*));
    va_list args;
    va_start(args, shaderInfo);
    for(int i = 0; i < numShaders; i++) {
        shaders[i] = create_shader(shaderInfo.shaderType, shaderInfo.shaderPath);
        glAttachShader(program->id, shaders[i]->id);
        shaderInfo = va_arg(args, shader_information_t);
    }
    program->attachedShaders = shaders;
    program->attachedShadersSize = numShaders;
    compile_program(program);
    return program;
}