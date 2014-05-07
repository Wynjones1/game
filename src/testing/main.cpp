#include <iostream>
#include "window.h"

void draw_triangle(void)
{
	float vertices[] =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	unsigned short indices[] =
	{
		0, 1, 2
	};

	GLuint vertexbuffer, indexbuffer, vertexarray;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBindVertexArray(0);

	glVertexAttrib3f(0, 0, 0, 0);
	glVertexAttrib3f(1, 1, 0, 0);
	glVertexAttrib3f(2, 0, 0, 1);
	glVertexAttrib2f(3, 0, 0);

	glBindVertexArray(vertexarray);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

Window init(void)
{
	Window window = Window(400, 400);

	Shader vert = Shader(GL_VERTEX_SHADER, "./data/testing.vertex");
	Shader frag = Shader(GL_FRAGMENT_SHADER, "./data/testing.fragment");

	Program program = Program();
	program.AddShader(vert);
	program.AddShader(frag);
	program.Compile();

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
	draw_triangle();
	w.SwapBuffer();
	SDL_Delay(1000);
	return 0;
}