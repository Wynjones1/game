#include <iostream>
#include "window.h"

void draw_triangle(void)
{
	float vertices[] =
	{
		-1.0f,-1.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	float texcoords[] =
	{
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	unsigned short indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	GLuint vertexbuffer, texbuffer, indexbuffer, vertexarray;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &texbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);
		//Setup and enable the vertex data on the gpu.
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		//as above but for texture data.
		glBindBuffer(GL_ARRAY_BUFFER, texbuffer);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBindVertexArray(0);

	glVertexAttrib3f(0, 0, 0, 0);
	glVertexAttrib3f(1, 1, 0, 0);
	glVertexAttrib3f(2, 0, 0, 1);
	glVertexAttrib2f(3, 0, 0);

	//Set up the texture.
	Texture tex = Texture("./data/grid.ppm");

	glBindVertexArray(vertexarray);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(*indices), GL_UNSIGNED_SHORT, 0);
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
	SDL_Delay(1000);
	return 0;
}