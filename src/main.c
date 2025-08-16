
#include <stdio.h>
#include <time.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "string_t.h"

#include "window/window.h"
#include "window/events.h"
#include "graphics/shader.h"
#include "graphics/texture.h"

#include <png.h>

float vertices[] = {
        -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main() {
    // 1. Инициализация GLFW
    
    init_window(1280, 720, "Hellow Open GELL");
    init_events();

    time_t mytime = time(NULL);
    struct tm *now = localtime(&mytime);
    int c = 0;
    int cs = 0;
    int s = now->tm_sec;


    // Работа с шейдорами
    Shader* shader = init_shaders("shaders/texture.vert", "shaders/texture.frag");

    if (shader == NULL || shader->id == 0) {
        glfwTerminate();
        printf("Error, no shader!!!\n");
        return 1;
    }

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));  // v_textCoord
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    // endWorkWithShaders

    Texture* texture = init_texture("textures/rgbTest.png");
    if (texture == NULL || texture->id == 0) {

        free_shader(shader);
        glfwTerminate();
        printf("Error, no texture!!!\n");
        return 1;
    }

    glClearColor(0, 0, 0, 1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!window_should_close()) {
        pull_events();

        if (events_jpressed(GLFW_KEY_ESCAPE)) {
            window_set_should_close(1);
        }

        if (events_clicked(GLFW_MOUSE_BUTTON_LEFT)) {
            glClearColor(0.75, 0.1, 0.2, 1);
        }

        if (events_clicked(GLFW_MOUSE_BUTTON_RIGHT)) {
            glClearColor(0, 0, 0, 1);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Рисуем triangles
        use_shader(shader);

        bind_texture(texture);

        glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

        window_swap_buffer();

        if (s != now->tm_sec) {
            printf("Time pass 1s : %d\n", c);
            cs++;
            s = now->tm_sec;
            c = 0;
        }
        time(&mytime);
        now = localtime(&mytime);
        c++;
    }

    printf("nepon\n");

    free_shader(shader);
    free_texture(texture);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    free_window();
    free_events();

    

    glfwTerminate();
    return 0;
}
