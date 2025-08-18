
#include <stdio.h>
#include <time.h>

#define GLEW_STATIC

#define _USE_MATH_DEFINES // for C
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string_t.h>
#include <matrix4.h>

#include "window/window.h"
#include "window/events.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "camera/camera.h"

float vertices[] = {
		// x    y     z     u     v
	   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

static void print_matr4(Matrix4 mat) {
    printf("Matrix4: \n");
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}


void move_player(Camera* camera) {
    if (events_pressed(GLFW_KEY_W)) {
            float* pos = camera_get_position(camera);
            pos[2] += 0.016f;
    }

    if (events_pressed(GLFW_KEY_S)) {
            float* pos = camera_get_position(camera);
            pos[2] -= 0.016f;
    }

    if (events_pressed(GLFW_KEY_A)) {
            float* pos = camera_get_position(camera);
            pos[0] -= 0.016f;
    }

    if (events_pressed(GLFW_KEY_D)) {
            float* pos = camera_get_position(camera);
            pos[0] += 0.016f;
    }

    if (events_pressed(GLFW_KEY_I)) {
            float* pos = camera_get_position(camera);
            pos[1] += 0.016f;
    }

    if (events_pressed(GLFW_KEY_O)) {
            float* pos = camera_get_position(camera);
            pos[1] -= 0.016f;
    }

    if (events_pressed(GLFW_KEY_Q)) {
            camera_rotate(camera, 0 , -0.016f , 0);
    }

    if (events_pressed(GLFW_KEY_E)) {
            camera_rotate(camera, 0, 0.016f , 0);
    }

    if (events_jmouse_move() && 0) {
        int w, h;
        window_get_size(&w, &h);

        FRect mp = events_mouse_position();

        camera_rotate(camera, 0, -(mp.w / ((float) w)), 0);
    }
}

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
    Shader* shader = init_shaders("shaders/textureCamera.vert", "shaders/texture.frag");

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

    glClearColor(0, 0, 0, 0);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Vector3 pos = {0, 0, 10};
    Camera* camera = init_camera(pos, 120, 0, 0, 0);

    Matrix4 model, proj, view;
    
    mat4_set_scale(model, 0.2f);
    //mat4_set_rotade_d(model, 90, 2);
    //mat4_mul_scale(model, 0.2f);
    //mat4_mul_translate(model, 0.2f, 0, 0);
    
    //mat4_set_translate(model, 1, 1, 0);
    //setEMatrix4(model, 1.0f);

    setEMatrix4(proj, 1.0f);
    setEMatrix4(view, 1.0f);
    //mat4_set_rotade_d(view, 90, 2);


    while (!window_should_close()) {
        pull_events();

        if (events_jpressed(GLFW_KEY_ESCAPE)) {
            window_set_should_close(1);
        }

        if (events_clicked(GLFW_MOUSE_BUTTON_LEFT)) {
            glClearColor(0.9, 0.9, 0.9, 1);
        }

        if (events_clicked(GLFW_MOUSE_BUTTON_RIGHT)) {
            glClearColor(0, 0, 0, 1);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // Рисуем triangles

        move_player(camera);

        
        use_shader(shader);

        camera_set_projection(camera, proj);
        camera_set_view(camera, view);

        uniform_matrix_shader(shader, "model", model);
        uniform_matrix_shader(shader, "proj", proj);
        uniform_matrix_shader(shader, "view", view);

        //mat4_mul_translate(model, 0, 0, -1.0f);

        bind_texture(texture);

        glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

        window_swap_buffer();

        if (s != now->tm_sec) {
            print_matr4(view);
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
    free_camera(camera);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    free_window();
    free_events();

    

    glfwTerminate();
    return 0;
}
