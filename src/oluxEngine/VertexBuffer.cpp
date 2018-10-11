#include "VertexBuffer.h"

#include <iostream>

namespace OluxEngine
{
	VertexBuffer::VertexBuffer() : numOfComponents(0), dirty(false)
	{
		glGenBuffers(1, &id);

		if (!id)
		{
			std::cout << "COULDNT GEN VBO" << std::endl;
			throw std::exception();
		}
	}

	void VertexBuffer::add(glm::vec2 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 2;
		}

		if (numOfComponents != 2)
		{
			std::cout << "num of components != 2" << std::endl;
			throw std::exception();
		}

		data.push_back(value.x);
		data.push_back(value.y);
		dirty = true;
	}

	void VertexBuffer::add(glm::vec3 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 3;
		}

		if (numOfComponents != 3)
		{
			std::cout << "num of components != 3" << std::endl;
			throw std::exception();
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		dirty = true;
	}

	void VertexBuffer::add(glm::vec4 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 4;
		}

		if (numOfComponents != 4)
		{
			std::cout << "num of components != 4" << std::endl;
			throw std::exception();
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		data.push_back(value.w);
		dirty = true;
	}

	int VertexBuffer::getDataSize()
	{
		return data.size();
	}

	int VertexBuffer::getNumOfComponents()
	{
		if (!numOfComponents)
		{
			std::cout << "Couldnt get numofcomponents" << std::endl;
			throw std::exception();
		}

		return numOfComponents;
	}

	GLuint VertexBuffer::getId()
	{
		if (dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.at(0), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			dirty = false;
		}

		return id;
	}
}