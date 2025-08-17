
#ifndef __SHADER_H
#define __SHADER_H 1

#include <stdint.h>

#include <string_t.h>
#include <matrix4.h>

typedef struct {
    GLuint id;
} Shader;

void use_shader(Shader* shader);
void uniform_matrix_shader(Shader* shader, String name, Matrix4 matrix4);

Shader* init_shaders(const String vertexFile, const String fragmentFile);
void free_shader(Shader* shader);

#endif