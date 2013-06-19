#include "init.h"
#include <stdlib.h>
#include "callbacks.h"

GLFWwindow *init(void)
{
	GLFWwindow *window;

	if(!glfwInit())
		abort();

	window = glfwCreateWindow(640, 640, "Hello, world.", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		abort();
	}

	glfwSetKeyCallback(window, (GLFWkeyfun) callback_key);
	glfwSetFramebufferSizeCallback(window, callback_fb_resize);

	glfwMakeContextCurrent(window);
	return window;	
}
