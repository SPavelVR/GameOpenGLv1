
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.h"
#include "loadsys/loadshaders.h"

void use_shader(Shader* shader) {
    if (shader == NULL) return  ;
    
    glUseProgram(shader->id);
};

void uniform_matrix_shader(Shader* shader, String name, Matrix4 matrix4) {
    if (shader == NULL || name == NULL || shader->id == 0) return   ;

    GLuint translate = glGetUniformLocation(shader->id, name);
    mat4_trans(matrix4);
    glUniformMatrix4fv( translate, 1, GL_FALSE, (float*) matrix4);
    mat4_trans(matrix4);
};

Shader* init_shaders(const String vertexFile, const String fragmentFile) {
    Shader* shader = load_shaders(vertexFile, fragmentFile);
    return shader;
};

void free_shader(Shader* shader) {
    if (shader == NULL) return  ;

    if (shader->id != 0) {
        glDeleteProgram(shader->id);
        shader->id = 0;
    }

    free(shader);
}