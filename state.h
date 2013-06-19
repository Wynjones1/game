#ifndef STATE_H
#define STATE_H
#include <GLFW/glfw3.h>
#include <containers/list.h>

typedef struct
{
	int up, down, left, right, debug, space, grid;
	list_t      *objects;
	GLFWwindow  *window;
}state_t;

void state_init(state_t *state);
void state_add_object(state_t *state, void *object);
#endif
