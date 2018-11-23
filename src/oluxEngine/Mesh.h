#ifndef OLUXENGINE_MESH_H
#define OLUXENGINE_MESH_H

#include "Resource.h"
#include "VertexArray.h"
#include "Face.h"

#include <memory>
#include <glm/glm.hpp>
#include <vector>

namespace OluxEngine
{
	class Mesh : public Resource
	{
		public:
			static std::shared_ptr<Mesh> Load(std::string path);
			// static std::shared_ptr<Mesh> Create(unsigned int width, unsigned int height, unsigned char* data);

            std::shared_ptr<VertexArray> getShape();
			std::vector<Face> getFaces();
			glm::vec3 getSize();

        private:
            std::shared_ptr<VertexArray> shape;
	};
}

#endif