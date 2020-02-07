#include "Texture.h"

#include <iostream>
#include <glew.h>
#include "stb/stb_image.h"

int width, height, nrChannels;

unsigned int Texture::Create2D(const char* filename)
{
	// load image, create texture and generate mipmaps
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	void* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	unsigned int GLtexture = 0;
	glGenTextures(1, &GLtexture);
	glBindTexture(GL_TEXTURE_2D, GLtexture);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (nrChannels == 1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	if (data && nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (data && nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	return GLtexture;
}

unsigned int Texture::Create3D(int width, int height, int depth, void * data)
{
	return 0;
}

unsigned int Texture::CreateEmpty2D(int width, int height)
{
	return 0;
}

unsigned int Texture::CreateEmpty3D(int width, int height, int depth)
{
	return 0;
}

unsigned int Texture::FillData2D(void * data)
{
	return 0;
}

unsigned int Texture::FillData3D(void * data)
{
	return 0;
}
