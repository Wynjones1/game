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
	Drawable(Program &program);
	virtual void Draw() = 0;
	virtual void Simulate(float dt) = 0;
	virtual glm::mat4 GetModelMatrix() = 0;
	glm::mat4 model;
	Program &program;
	bool alive;
};

class Mesh : public Drawable
{
public:
	Mesh(Program &program);
	Mesh(Program &program, const char *filename);

	void Draw();
	void Simulate(float dt);

	void AddVertex(double *data);
	void AddVertex(double v0, double v1, double v2);

	void AddNormal(double *data);
	void AddNormal(double n0, double n1, double n2);

	void AddTexcoord(double *data);
	void AddTexcoord(double t0, double t1);

	void AddColour(double *data);
	void AddColour(double c0, double c1, double c2);

	void AddFace(int *data);
	void AddFace(int f0, int f1, int f2);

	void InitBuffers(void);

	glm::vec3 pos;
	glm::mat4 GetModelMatrix();

	Texture *texture;

private:
	std::vector<float>    vertices;
	std::vector<float>    colours;
	std::vector<float>    normals;
	std::vector<float>    texcoords;
	std::vector<GLushort> faces;

	GLuint vao, vbuffer, nbuffer, tbuffer, fbuffer, cbuffer;

	void ReadHeader(FILE *fp, int &num_vertices, int &num_faces, bool &have_normals, bool &have_tex);
	void ReadVertexData(FILE *fp, int num, bool have_normals, bool have_tex);
	void ReadFaceData(FILE *fp, int num);
};

class Axis : public Drawable
{
public:
	Axis(Program &program)
	: Drawable(program)
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

	void Draw()
	{
		program.Use();
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 18);
		glBindVertexArray(0);
	}

	void Simulate(float dt)
	{
	
	}

	glm::mat4 GetModelMatrix(void)
	{
		return glm::mat4(1.0);
	}
private:
	GLuint vao, buffers[2];
};
