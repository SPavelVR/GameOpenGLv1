
#include <stdlib.h>

#include "util.h"

#include "window/window.h"

typedef struct Window {
    GLFWwindow* window;
    int width;
    int height;
    char* title;
} Window;

static Window* window = NULL;

int init_window(int width, int height, const String title) {
    if (window == NULL) {
        window = calloc(1, sizeof(Window));
        check_ptr(window);
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    window->width = width;
    window->height = height;
    window->title = strinit(title);

    check_ptr(window->window);

    glfwMakeContextCurrent(window->window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Error! no init glew!\n");
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, width, height);

    return 0;
};

void free_window() {
    if (window->title != NULL) strfree(window->title);
    free(window);
    window = NULL;
};

int window_should_close() {
    return glfwWindowShouldClose(window->window);
};

void window_swap_buffer() {
    glfwSwapBuffers(window->window);
}

void window_set_size(int width, int height) {
    window->width = width;
    window->height = height;
};

void window_get_size(int* width, int* height) {
    *width = window->width;
    *height = window->height;
}; 

GLFWwindow* get_window() {
    return window->window;
};

void window_set_should_close(int flag) {
    glfwSetWindowShouldClose(window->window, flag);
};