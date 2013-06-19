#include "callbacks.h"

state_t *new;
state_t *old;
void callbacks_register_state(state_t *new_in, state_t *old_in)
{
	new = new_in;	
	old = old_in;
}

int callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS || action == GLFW_RELEASE)
	{
		switch(key)
		{
			case GLFW_KEY_W:	
				new->up = action;
				break;
			case GLFW_KEY_A:
				new->left = action;
				break;
			case GLFW_KEY_S:
				new->down = action;
				break;
			case GLFW_KEY_D:
				new->right = action;
				break;
			case GLFW_KEY_SPACE:
				new->space = action;
				break;
			case GLFW_KEY_Q:
				if(action == GLFW_PRESS)
					new->debug = 1 - new->debug;
				break;
			case GLFW_KEY_G:
				if(action == GLFW_PRESS)
					new->grid = 1 - new->grid;
				break;
			case GLFW_KEY_R:
				break;
		}
	}
	return 1;
}
void callback_fb_resize(GLFWwindow *window, int width, int height)
{
	int size = (width < height) ? width : height;
	glViewport(0, 0, size, size);
}
