#include <iostream>
#include "window.h"

void draw_triangle(void)
{
}

Window init(void)
{
	Window window = Window(400, 400);

	Shader vert = Shader(GL_VERTEX_SHADER, "./data/simple.vertex");
	Shader frag = Shader(GL_FRAGMENT_SHADER, "./data/simple.fragment");

	Program program = Program();
	program.AddShader(vert);
	program.AddShader(frag);
	program.Compile();

	program.Use();

	//glUniform1i(glGetUniformLocation(program.program_id, "sampler0"), 0);

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
	draw_triangle();
	w.SwapBuffer();
	SDL_Event event;
	int c = 0;
	SDL_GameController *gc = SDL_GameControllerOpen(0);
	if(!gc) return 0;
	std::cout << "Opened the joystick." << std::endl;

	while(1)
	{
		while(SDL_PollEvent(&event))
		{
			std::cout << "Got an event " << c++ << std::endl;
			if(event.type == SDL_KEYDOWN) return 0;
		}
	}
	return 0;
}
