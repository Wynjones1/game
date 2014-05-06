#include "shaders.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Shader::Shader(GLenum type, const char *filename)
	: type(type)
{
	/* Read in the shader source. */
	FILE *fp  = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	long int count = ftell(fp);
	char *source = (char*)calloc(1, count + 1);
	fseek(fp, 0, SEEK_SET);
	fread(source, 1, count, fp);

	/* Allocate the shader object and create the shader */
	shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, (const GLchar **)&source, NULL);
	glCompileShader(shader_id);

	/* Check that the shader has been successfully created */
	GLint status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buf[1024];
		glGetShaderInfoLog(shader_id, 1024, NULL, buf);
		std::cout << "Error creating shader: " 
				  << filename 
				  << " :" 
				  << buf
				  << std::endl;
		exit(-1);
	}
}
Program::Program()
{
	program_id = glCreateProgram();
}

void Program::AddShader(const Shader &shader)
{
	glAttachShader(program_id, shader.shader_id);
}

void Program::Compile()
{
	glLinkProgram(program_id);
	GLint status;
	glGetProgramiv(program_id, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buf[1024];
		glGetProgramInfoLog(program_id, 1024, NULL, buf);
		std::cout << "Could not compile program: "
				  << buf
				  << std::endl;
		exit(-1);
	}
	model      = glGetUniformLocation(program_id, "model");
	view       = glGetUniformLocation(program_id, "view");
	projection = glGetUniformLocation(program_id, "projection");
}

void Program::Use()
{
	glUseProgram(program_id);
}
