#include "Texture.h"

#include <iostream>
#include <glew.h>
#include "stb/stb_image.h"

int width, height, nrChannels;

unsigned int Texture::Create2D(const char* filename)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
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
