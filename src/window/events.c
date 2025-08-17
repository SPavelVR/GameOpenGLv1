
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "util.h"

#include "window/events.h"

typedef struct Events {
    uint8_t* _keys;
    uint64_t* _frames;
    uint64_t _current;
    uint8_t* _mouse_button;
    uint64_t* _mouse_frames;
    float deltaX;
    float deltaY;
    float x;
    float y;
    uint64_t _cursor_frames;
    uint8_t _cursor_locked;
    uint8_t _cursor_started;
} Events;

static Events* events = NULL;

// CALLBACKS --------------------------------------------

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (events->_cursor_started) {
        events->deltaX = xpos - events->x;
        events->deltaY = ypos - events->y;
    } else {
        events->_cursor_started = 1;
    }
    events->_cursor_frames = events->_current;
    events->x = (float) xpos;
    events->y = (float) ypos;
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        events->_mouse_button[button] = 1;
        events->_mouse_frames[button] = events->_current;
    } else if (action == GLFW_RELEASE) {
        events->_mouse_button[button] = 0;
        events->_mouse_frames[button] = events->_current;
    }
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        events->_keys[key] = 1;
        events->_frames[key] = events->_current;
    } else if (action == GLFW_RELEASE) {
        events->_keys[key] = 0;
        events->_frames[key] = events->_current;
    }
};

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    window_set_size(width, height);
}

// END CALLBACK ---------------------------------------------------

int init_events() {
    if (events == NULL) {
        events = malloc(sizeof(Events));

        check_ptr(events);

        memset(events, 0, sizeof(Events));
    }
    GLFWwindow* window = get_window();

    events->_keys = calloc(1024, sizeof(uint8_t));
    events->_frames = calloc(1024, sizeof(uint32_t));

    events->_mouse_button = calloc(8, sizeof(uint8_t));
    events->_mouse_frames = calloc(8, sizeof(uint32_t));

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    return 0;
};

void free_events() {
    if (events == NULL) return  ;

    if (events->_frames != NULL) free(events->_frames);
    if (events->_keys != NULL) free(events->_keys);

    if (events->_mouse_frames != NULL) free(events->_mouse_frames);
    if (events->_mouse_button != NULL) free(events->_mouse_button);

    free(events);
    events = NULL;
};

void pull_events() {

    events->_current++;

    glfwPollEvents();
};

int events_pressed(int keycode) {
    if (keycode < 0 || keycode >= 1024) return 0;

    return events->_keys[keycode];
};

int events_jpressed(int keycode) {
    if (keycode < 0 || keycode >= 1024) return 0;

    return events->_keys[keycode] && (events->_frames[keycode] == events->_current);
};

int events_clicked(int button) {
    if (button < 0 || button >= 8) return 0;

    return events->_mouse_button[button];
};

int events_jclicked(int button) {
    if (button < 0 || button >= 8) return 0;

    return events->_mouse_button[button] && (events->_mouse_frames[button] == events->_current);
};

int events_mouse_move() {
    if (events == NULL) return 0;
    return events->_cursor_started;
};
int events_jmouse_move() {
    if (events == NULL) return 0;
    return events->_cursor_started && (events->_cursor_frames == events->_current);
};

FRect events_mouse_position() {
    FRect rect;
    rect.x = events->x;
    rect.y = events->y;
    rect.w = events->deltaX;
    rect.h = events->deltaY;
    return rect;
};