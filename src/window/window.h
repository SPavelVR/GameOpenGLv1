
#ifndef __WINDOW_H
#define __WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "string_t.h"

int init_window(int width, int height, const String title);

void free_window();

int window_should_close();

void window_swap_buffer();

void window_set_should_close(int flag);

GLFWwindow* get_window();


#endif