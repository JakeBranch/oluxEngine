#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "Exception.h"

namespace OluxEngine
{
	class VertexBuffer
	{
		private:
			GLuint id;
			std::vector<GLfloat> data;
			int numOfComponents;
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