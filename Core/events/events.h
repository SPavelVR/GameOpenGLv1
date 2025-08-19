#ifndef __EVENTS_H
#define __EVENTS_H

#include "window/window.h"
#include "rect.h"

int init_events();

void free_events();

void pull_events();

int events_pressed(int keycode);
int events_jpressed(int keycode);

int events_clicked(int button);
int events_jclicked(int button);

int events_mouse_move();
int events_jmouse_move();

FRect events_mouse_position();

void events_tougle_cursor();
int events_get_cursor_mode();

#endif