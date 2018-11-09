#include "VertexBuffer.h"

#include <iostream>

namespace OluxEngine
{
	/**
	* Generates vertex buffer
	*/
	VertexBuffer::VertexBuffer() : numOfComponents(0), dirty(false)
	{
		glGenBuffers(1, &id);

		if (!id)
		{
			throw Exception("Failed to generate vertex buffer");
		}
	}

	/**
	* Add vec2 component
	*
	* Throws exception if previously added value has different number of components to currently added value.
	*/
	void VertexBuffer::add(glm::vec2 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 2;
		}

		if (numOfComponents != 2)
		{
			throw Exception("Failed to add component to vertex buffer");
		}

		data.push_back(value.x);
		data.push_back(value.y);
		dirty = true;
	}

	/**
	* Add vec3 component
	*
	* Throws exception if previously added value has different number of components to currently added value.
	*/
	void VertexBuffer::add(glm::vec3 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 3;
		}

		if (numOfComponents != 3)
		{
			throw Exception("Failed to add component to vertex buffer");
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		dirty = true;
	}

	/**
	* Add vec4 component
	*
	* Throws exception if previously added value has different number of components to currently added value.
	*/
	void VertexBuffer::add(glm::vec4 value)
	{
		if (!numOfComponents)
		{
			numOfComponents = 4;
		}

		if (numOfComponents != 4)
		{
			throw Exception("Failed to add component to vertex buffer");
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		data.push_back(value.w);
		dirty = true;
	}

	/**
	* Return size of buffer data
	*/
	int VertexBuffer::getDataSize()
	{
		return data.size();
	}

	/**
	* Return buffer data
	*/ 
	std::vector<GLfloat> VertexBuffer::getData()
	{
		return data;
	}

	/**
	* Return number of components 
	*/
	int VertexBuffer::getNumOfComponents()
	{
		if (!numOfComponents)
		{
			throw Exception("Failed to get number of components of vertex buffer");
		}

		return numOfComponents;
	}

	/**
	* Returns ID of buffer
	* 
	* Sets 'dirty' to false after first draw of new value.
	*/
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