#include "drawable.h"
#include <iostream>
#include <errno.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "defines.h"

Drawable::Drawable(Program &program)
: program(program)
{}

/* Read in the mesh from a ply file */
void Mesh::ReadHeader(FILE *fp, int &num_vertices, int &num_faces, bool &have_normals, bool &have_tex)
{
	char buf[1024];
	while(fgets(buf, 1024, fp))
	{
		sscanf(buf, "element vertex %d", &num_vertices);
		sscanf(buf, "element face %d", &num_faces);
		if(strcmp("propery float nx", buf) == 0)
		if(strncmp("propery float nx", buf, strlen("propery float nx")) == 0)
		{
			have_normals = true;
		}

		if(strncmp("propery float s", buf, strlen("propery float s")) == 0)
		{
			have_tex    = true;
		}

		if(strncmp("end_header", buf, strlen("end_header")) == 0)
		{
			return;
		}
	}
}

void Mesh::ReadVertexData(FILE *fp, int num, bool have_normals, bool have_tex)
{
	double n[3];
	double v[3];
	double t[2];
	char buf[1024];
	for(int i = 0; i < num; i++)
	{
		fgets(buf, 1024, fp);
		if(have_normals && have_tex)
		{
			sscanf(buf, "%lf %lf %lf %lf %lf %lf %lf %lf", v, v+1, v+2, n, n+1, n+2, t, t+1);
			AddVertex(v);
			AddNormal(n);
			AddTexcoord(t);
		}
		else if(have_normals)
		{
			sscanf(buf, "%lf %lf %lf %lf %lf %lf", v, v+1, v+2, n, n+1, n+2);
			AddVertex(v);
			AddNormal(n);
		}
		else if(have_tex)
		{
			sscanf(buf, "%lf %lf %lf %lf %lf", v, v+1, v+2, t, t+1);
			AddVertex(v);
			AddTexcoord(t);
		}
		else
		{
			sscanf(buf, "%lf %lf %lf", v, v+1, v+2);
			AddVertex(v);
		}
	}
}

void Mesh::ReadFaceData(FILE *fp, int num)
{
	int f[4];
	char buf[1024];
	for(int i = 0; i < num; i++)
	{
		fgets(buf, 1024, fp);
		if(sscanf(buf, "%*d %d %d %d %d", f, f+1, f+2, f+3) == 4)
		{
			AddFace(f[0], f[1], f[2]);
			AddFace(f[2], f[3], f[0]);
		}
		else if(sscanf(buf, "%*d %d %d %d" , f, f+1, f+2) == 3)
		{
			AddFace(f[0], f[1], f[2]);
		}
	}
}

Mesh::Mesh(Program &program, const char *filename)
	: Drawable(program)
	, vbuffer(-1)
	, nbuffer(-1)
	, tbuffer(-1)
	, fbuffer(-1)
	, texture(NULL)
{
	FILE *fp = fopen(filename, "r");
	if(!fp)
	{
		std::cout << "Could not open file: " << filename << " :" << strerror(errno) << std::endl;
		exit(-1);
	}

	int  num_vertices, num_faces;
	bool have_normals = false;
	bool have_tex = false;
	//Read the header
	ReadHeader(fp, num_vertices, num_faces, have_normals, have_tex);
	ReadVertexData(fp, num_vertices, have_normals, have_tex);
	ReadFaceData(fp, num_faces);

	InitBuffers();
}

Mesh::Mesh(Program &program)
	: Drawable(program)
	, vbuffer(-1)
	, nbuffer(-1)
	, tbuffer(-1)
	, fbuffer(-1)
	, texture(NULL)
{
	AddVertex(-1.0, -1.0, -1.0);
	AddVertex(-1.0, 1.0, -1.0);
	AddVertex(1.0, 1.0, -1.0);
	AddVertex(1.0, -1.0, -1.0);

	AddTexcoord(0, 1);
	AddTexcoord(0, 0);
	AddTexcoord(1, 0);
	AddTexcoord(1, 1);

	AddColour(1.0, 0.0, 0.0);
	AddColour(0.0, 1.0, 0.0);
	AddColour(0.0, 0.0, 1.0);
	AddColour(1.0, 1.0, 1.0);

	AddNormal(0.0, 0.0, 1.0);
	AddNormal(0.0, 0.0, 1.0);
	AddNormal(0.0, 0.0, 1.0);
	AddNormal(0.0, 0.0, 1.0);

	AddFace(0, 1, 2);
	AddFace(2, 3, 0);
	InitBuffers();
}

void Mesh::InitBuffers(void)
{
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	if(colours.size() == vertices.size())
	{
		glGenBuffers(1, &cbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, cbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0]) * colours.size(), colours.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	if(normals.size() == vertices.size())
	{
		glGenBuffers(1, &nbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	if(texcoords.size() / 2 == vertices.size() / 3)
	{
		glGenBuffers(1, &tbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords[0]) * texcoords.size(), texcoords.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(3);
	}

	glGenBuffers(1, &fbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces[0]) * faces.size(), faces.data(), GL_STATIC_DRAW);
}

void Mesh::Draw()
{
	if(texture)texture->Bind();
	glm::mat4 model = GetModelMatrix();
	glUniformMatrix4fv(program.model, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_SHORT, NULL);
}

void Mesh::AddFace(int *data)
{
	AddFace(data[0], data[1], data[2]);
}

void Mesh::AddFace(int f0, int f1, int f2)
{
	faces.push_back(f0);
	faces.push_back(f1);
	faces.push_back(f2);
}

void Mesh::AddVertex(double *data)
{
	AddVertex(data[0], data[1], data[2]);
}

void Mesh::AddNormal(double *data)
{
	AddNormal(data[0], data[1], data[2]);
}

void Mesh::AddTexcoord(double *data)
{
	AddTexcoord(data[0], data[1]);
}

void Mesh::AddVertex(double v0, double v1, double v2)
{
	vertices.push_back((float)v0);
	vertices.push_back((float)v1);
	vertices.push_back((float)v2);
}

void Mesh::AddNormal(double n0, double n1, double n2)
{
	normals.push_back((float)n0);
	normals.push_back((float)n1);
	normals.push_back((float)n2);
}

void Mesh::AddTexcoord(double t0, double t1)
{
	texcoords.push_back((float)t0);
	texcoords.push_back((float)t1);
}

void Mesh::AddColour(double *data)
{
	AddColour(data[0], data[1], data[2]);
}

void Mesh::AddColour(double c0, double c1, double c2)
{
	colours.push_back((float)c0);
	colours.push_back((float)c1);
	colours.push_back((float)c2);
}

glm::mat4 Mesh::GetModelMatrix()
{
	glm::mat4 out(1.0);
	return glm::translate(out, pos);
}
