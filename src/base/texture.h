#pragma once
#include <GL/gl3w.h>

class Texture
{
public:
		Texture(const char *filename);
		Texture();

		unsigned char *data;
		int            width;
		int            height;
		int            bpp;

		void ReadPPM(const char *filename);
		void ReadBMP(const char *filename);

		void InitTexture(void);
		void Bind(void);
		void Unbind(void);

		/* OpenGL State */
		GLuint texture;
		GLuint sampler;
};
