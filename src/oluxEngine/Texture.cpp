#include "Texture.h"
#include <iostream>
#include <exception>

namespace OluxEngine
{
	/**
	* Loads texture data from path
	*/
	std::shared_ptr<Texture> Texture::Load(std::string path)
	{
		const char* fileLoc = path.c_str();

		int w = 0;
		int h = 0;
		int channels = 0;

		unsigned char* data = stbi_load(fileLoc, &w, &h, &channels, STBI_rgb_alpha);
		if (!data)
		{
			std::string errorMessage = "Failed to load texture: ";
			errorMessage += path;
			throw Exception(errorMessage);
		}

		std::shared_ptr<Texture> rtn = Create(w, h, data);
		rtn->size.x = w;
		rtn->size.y = h;

		return rtn;
	}

	/**
	* Generates texture from texture data
	*/
	std::shared_ptr<Texture> Texture::Create(unsigned int width, unsigned int height, unsigned char* data)
	{
		std::shared_ptr<Texture> rtn = std::make_shared<Texture>();

		glGenTextures(1, &rtn->id);

		if (!rtn->id)
		{
			throw Exception("Failed to generate texture");
		}

		glBindTexture(GL_TEXTURE_2D, rtn->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		free(data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		//glActiveTexture(GL_TEXTURE0 + 1);
		//glBindTexture(GL_TEXTURE_2D, rtn->getId());

		return rtn;
	}

	/**
	* Returns ID of the texture
	*/
	GLuint Texture::getId()
	{
		return id;
	}
}