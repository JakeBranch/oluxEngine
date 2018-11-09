#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "Exception.h"

namespace OluxEngine
{
	class VertexBuffer
	{
		private:
			/**
			* ID of the vertex buffer
			*/
			GLuint id;

			/**
			* Vertex buffer data
			*/
			std::vector<GLfloat> data;

			/**
			* Number of components
			*/
			int numOfComponents;

			/**
			*Flag to check if buffers need to be bound before drawing.
			*Set to false after first draw.
			*/
			bool dirty;

		public:
			VertexBuffer();
			void add(glm::vec2 value);
			void add(glm::vec3 value);
			void add(glm::vec4 value);
			int getNumOfComponents();
			int getDataSize();
			std::vector<GLfloat> getData();
			GLuint getId();
	};
}