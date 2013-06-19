#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <GLFW/glfw3.h>
#include "state.h"

void callbacks_register_state(state_t *new, state_t *old);
int callback_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void callback_fb_resize(GLFWwindow *window, int width, int height);

#endif
