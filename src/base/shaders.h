#pragma once
#include <GL/gl3w.h>

class Shader
{
public:
	Shader(GLenum type, const char *filename);
	GLuint shader_id;
	GLenum type;
};

class Program
{
public:
	Program();
	void   AddShader(const Shader &shader);
	void   Compile();
	void   Use();
	GLuint program_id;
	GLuint model, view, projection;
};
