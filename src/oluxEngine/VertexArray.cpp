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
			std::cout << "COULDNT GENERATE VERTEX ARRAY" << std::endl;
			throw std::exception();
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
			std::cout << "Couldnt set buffer: " << attribute << std::endl;
			throw std::exception();
		}

		dirty = true;
	}

	int VertexArray::getVertexCount()
	{
		if (!buffers.at(0))
		{
			std::cout << "COULDNT GET VERT COUNT" << std::endl;
			throw std::exception();
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