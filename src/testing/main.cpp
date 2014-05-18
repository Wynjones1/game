#include <iostream>
#include "window.h"
#include "shaders.h"
#include <glm/glm.hpp>
#include <GL/gl3w.h>

Window init(void)
{
	Window window = Window(400, 400);

	Program program = Program("./data/simple.vertex", "./data/simple.fragment");

	program.Use();

	glm::mat4 temp_uniform = glm::mat4(1.0);
	glUniformMatrix4fv(program.model,      1, GL_FALSE, &temp_uniform[0][0]);
	glUniformMatrix4fv(program.view,       1, GL_FALSE, &temp_uniform[0][0]);
	glUniformMatrix4fv(program.projection, 1, GL_FALSE, &temp_uniform[0][0]);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	return window;
}

int main(int argc, char **argv)
{
	Window w = init();
	w.SwapBuffer();
	return 0;
}
