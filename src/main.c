
#include <stdio.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "string_t.h"

#include "window/window.h"
#include "window/events.h"

#include <png.h>

// git commit -m "добавлены файлы rect, point и добавлены функции в events: events_mouse_move, events_jmose_move и events_mouse_position."

int main() {
    // 1. Инициализация GLFW

    init_window(1280, 720, "Hellow Open GELL");
    init_events();

    glClearColor(0, 0, 0, 1);
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

        window_swap_buffer();
    }

    printf("zdesj PNG\n");

    free_window();
    free_events();

    glfwTerminate();
    return 0;
}
