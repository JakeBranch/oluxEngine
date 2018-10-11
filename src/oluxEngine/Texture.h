#ifndef OLUXENGINE_TEXTURE_H
#define OLUXENGINE_TEXTURE_H

#include "Resource.h"

#include <GL\glew.h>
#include <stb_image/stb_image.h>

#include <string>
#include <memory>

namespace OluxEngine
{
	class Texture : public Resource
	{
		GLuint id;
		bool dirty;
		int type;

		public:
			static std::shared_ptr<Texture> Load(std::string path);
			static std::shared_ptr<Texture> Create(unsigned int width, unsigned int height, unsigned char* data);
			GLuint getId();
	};
}

#endif