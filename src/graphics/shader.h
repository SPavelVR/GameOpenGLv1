
#ifndef __SHADER_H
#define __SHADER_H 1

#include <stdint.h>

#include <string_t.h>

typedef struct {
    GLuint id;
} Shader;

void use_shader(Shader* shader);

Shader* init_shaders(const String vertexFile, const String fragmentFile);
void free_shader(Shader* shader);

#endif