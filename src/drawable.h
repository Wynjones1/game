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
	virtual glm::mat4 GetModelMatrix() = 0;
	glm::mat4 model;
	Program &program;
};

class Mesh : public Drawable
{
public:
	Mesh(Program &program);
	Mesh(Program &program, const char *filename);

	void Draw();

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

	GLuint vbuffer, nbuffer, tbuffer, fbuffer, cbuffer;

	void ReadHeader(FILE *fp, int &num_vertices, int &num_faces, bool &have_normals, bool &have_tex);
	void ReadVertexData(FILE *fp, int num, bool have_normals, bool have_tex);
	void ReadFaceData(FILE *fp, int num);
};
