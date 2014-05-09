#pragma once 
#include "object.h"

class Mesh : public StaticObject
{
public:
	Mesh();
	Mesh(const char *filename);

	void Draw(Program &program);

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