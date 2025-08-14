
#ifndef __EVENTS_H
#define __EVENTS_H

#include "window/window.h"

int init_events();

void free_events();

void pull_events();

int events_pressed(int keycode);
int events_jpressed(int keycode);

int events_clicked(int button);
int events_jclicked(int button);

#endif