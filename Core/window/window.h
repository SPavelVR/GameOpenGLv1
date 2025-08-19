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

void window_set_size(int width, int height);
void window_get_size(int* width, int* height);

GLFWwindow* get_window();

void window_set_cursor_mode(int mode);


#endif