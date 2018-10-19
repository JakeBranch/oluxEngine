#include "VertexArray.h"
#include "VertexBuffer.h"

#include <iostream>

namespace OluxEngine
{
	VertexArray::VertexArray() : dirty(false)
	{
		glGenVertexArrays(1, &id);

		if (!id)
		{
			throw Exception("Failed to generate vertex array");
		}

		buffers.resize(10);
	}

	void VertexArray::setBuffer(std::string attribute, std::weak_ptr<VertexBuffer> buffer)
	{
		if (attribute == "in_Position")
		{
			buffers.at(0) = buffer.lock();
		}
		else if (attribute == "in_Color")
		{
			buffers.at(1) = buffer.lock();
		}
		else if (attribute == "in_TexCoord")
		{
			buffers.at(2) = buffer.lock();
		}
		else
		{
			std::string errorMessage = "Failed to set buffer attribute: ";
			errorMessage += attribute;
			throw Exception(errorMessage);
		}

		dirty = true;
	}

	int VertexArray::getVertexCount()
	{
		if (!buffers.at(0))
		{
			throw Exception("Failed to get vertex count");
		}

		return buffers.at(0)->getDataSize() / buffers.at(0)->getNumOfComponents();
	}

	GLuint VertexArray::getId()
	{
		if (dirty)
		{
			glBindVertexArray(id);

			for (size_t i = 0; i < buffers.size(); i++)
			{
				if (buffers.at(i))
				{
					glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());

					glVertexAttribPointer(i, buffers.at(i)->getNumOfComponents(), GL_FLOAT, GL_FALSE,
						buffers.at(i)->getNumOfComponents() * sizeof(GLfloat), (void *)0);

					glEnableVertexAttribArray(i);
				}
				else
				{
					glDisableVertexAttribArray(i);
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			dirty = false;
		}

		return id;
	}
}