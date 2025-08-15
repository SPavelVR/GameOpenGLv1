
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "loadsys/loadshaders.h"


Shader* load_shaders(const String vertexFile, const String fragmentFile) {
    GLchar* vertexCode = freadall(vertexFile);
    GLchar* fragmentCode = freadall(fragmentFile);

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const GLchar* const*)&vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        infoLog[511] = '\0';

        strfree(vertexCode);
        strfree(fragmentCode);

        printf("SHADER VERTEX ERROR: COMPILE FALL :\n%s", infoLog);
        return NULL;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const GLchar* const*)&fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        infoLog[511] = '\0';

        strfree(vertexCode);
        strfree(fragmentCode);

        printf("SHADER FRAGMENT ERROR: COMPILE FALL :\n%s", infoLog);
        return NULL;
    }

    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        infoLog[511] = '\0';
        printf("SHADER FRAGMENT ERROR: COMPILE FALL :\n%s", infoLog);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);

        strfree(vertexCode);
        strfree(fragmentCode);

        return NULL;
    }

    glDetachShader(id, vertex);
    glDetachShader(id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);   

    strfree(vertexCode);
    strfree(fragmentCode);

    Shader* shader = calloc(1, sizeof(Shader));

    if (shader == NULL) return NULL;
    shader->id = id;
    return shader;
};