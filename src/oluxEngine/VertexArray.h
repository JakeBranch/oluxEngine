#include <GL\glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

#include "Exception.h"

namespace OluxEngine
{
	class VertexBuffer;

	class VertexArray
	{
		GLuint id;
		bool dirty;
		std::vector<std::shared_ptr<VertexBuffer>> buffers;

		void splitStringWhitespace(std::string& input, std::vector<std::string>& output);
  		void splitString(std::string& input, char splitter, std::vector<std::string>& output);

		std::vector<GLfloat> position;
		std::vector<GLfloat> texCoord;
		std::vector<GLfloat> normal;
		std::vector<GLfloat> color;

	public:
		VertexArray();
		VertexArray(std::string path);

		void setBuffer(std::string attribute, std::weak_ptr<VertexBuffer> buffer);
		int getVertexCount();
		GLuint getId();

		std::vector<GLfloat> getPosition();
		std::vector<GLfloat> getTexCoord();
		std::vector<GLfloat> getNormal();
		std::vector<GLfloat> getColor();
	};
}