#include <GL/glew.h>
#include <glm.hpp>

#include <vector>

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
			void add(glm::vec3 value);
			void add(glm::vec4 value);
			int getNumOfComponents();
			int getDataSize();
			GLuint getId();
	};
}