#pragma once
#include <vector>
#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "shaders.h"
#include <stdio.h>

class Drawable
{
public:
	virtual void Draw(Program &program) = 0;
};

class Axis : public Drawable
{
public:
	Axis()
	: Drawable()
	{
		float vertex_data[] = 
		{
			0, 0, 0,
			1, 0, 0,
			0, 0, 0,
			0, 1, 0,
			0, 0, 0,
			0, 0, 1
		};

		float colour_data[] =
		{
			1, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 1
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(2, buffers);

		glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colour_data), colour_data, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void Draw(Program &program)
	{
		glUniformMatrix4fv(program.model, 1, GL_FALSE, &glm::mat4(1.0)[0][0]);
		glUniform1i(program.has_texture, 0);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 18);
		glBindVertexArray(0);
	}

	void Simulate(float dt)
	{
	
	}

private:
	GLuint vao, buffers[2];
};
