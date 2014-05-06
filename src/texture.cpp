#include "texture.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool ends_with(const char *string, const char *test)
{
	int l0 = strlen(string);
	int l1 = strlen(test);
	if(l1 < l0)
	{
		return strcmp(string + l0 - l1, test) == 0;
	}
	return false;
}

#define EOF_ERROR(fp)\
	if(feof(fp))\
	{\
		fprintf(stderr, "Unexpected End of File.\n");\
		exit(-1);\
	}

void Texture::ReadPPM(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	const int buf_size = 1024;
	char buf[buf_size + 1];
	buf[buf_size] = '\0';
	fgets(buf, buf_size, fp);
	bpp = 24;
	EOF_ERROR(fp);
	if(strncmp(buf, "P3", 2) != 0)
	{
		fprintf(stderr, "Not a PPM file\n");
		exit(-1);
	}

	fgets(buf, buf_size, fp);
	EOF_ERROR(fp);
	while(strncmp(buf, "#", 1) == 0)
	{
		fgets(buf, buf_size, fp);
		EOF_ERROR(fp);
	}

	if(sscanf(buf, "%d %d", &width, &height) != 2)
	{
		fprintf(stderr, "File Dimentions not present\n");
		exit(-1);
	}

	EOF_ERROR(fp);
	fgets(buf, buf_size, fp);
	EOF_ERROR(fp);

	data = (unsigned char*) calloc(400 * 600, bpp / 8);
	unsigned char *d = data;
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				fgets(buf, buf_size, fp);
				int temp;
				sscanf(buf, "%d", &temp);
				*d++ = temp;
			}

		}
	}
}

void Texture::ReadBMP(const char *filename)
{

}

void Texture::InitTexture(void)
{
	//Read in the texture data.
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//Set the sampler.
	glGenSamplers(1, &sampler);
	glBindSampler(GL_TEXTURE0, sampler);
}

void Texture::Bind(void)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindSampler(GL_TEXTURE0, sampler);
}

Texture::Texture(const char *filename)
{
	if(ends_with(filename, ".bmp"))
	{
		ReadBMP(filename);
	}
	else if(ends_with(filename, ".ppm"))
	{
		ReadPPM(filename);
	}
	InitTexture();
}

Texture::Texture()
	: width(4)
	, height(4)
	, bpp(24)
{
	data = new unsigned char[width * height * bpp / 8];
	data[0] = 255;
	data[1] = 0;
	data[2] = 0;

	data[3] = 0;
	data[4] = 255;
	data[5] = 0;

	data[6] = 0;
	data[7] = 0;
	data[8] = 255;

	data[9]  = 255;
	data[10] = 255;
	data[11] = 255;
}
