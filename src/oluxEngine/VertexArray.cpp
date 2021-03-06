#include "VertexArray.h"
#include "VertexBuffer.h"

#include <fstream>
#include <iostream>

namespace OluxEngine
{
	/**
	* Generates vertex array and loads mesh from 'path' 
	*/
	VertexArray::VertexArray(std::string path) : dirty(false)
	{
		glGenVertexArrays(1, &id);

		if(!id)
		{
			throw Exception("Failed to generate vertex array");
		}

		buffers.resize(10);
		std::ifstream file(path.c_str());

		if(!file.is_open())
		{
			throw Exception("Failed to open file");
		}

		std::string line;
		std::vector<std::string> splitLine;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;

	
		std::shared_ptr<VertexBuffer> positionBuffer;
		std::shared_ptr<VertexBuffer> texCoordBuffer;
		std::shared_ptr<VertexBuffer> normalBuffer;

		while(!file.eof())
		{
			std::getline(file, line);
			if(line.length() < 1) continue;
			splitStringWhitespace(line, splitLine);
			if(splitLine.size() < 1) continue;

			if(splitLine.at(0) == "v")
			{
				if(!positionBuffer) positionBuffer = std::make_shared<VertexBuffer>();

				positions.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));
			}
			else if(splitLine.at(0) == "vt")
			{
				if(!texCoordBuffer) 
				{
					texCoordBuffer = std::make_shared<VertexBuffer>();
				}

				texCoords.push_back(glm::vec2(
					atof(splitLine.at(1).c_str()),
					1.0f - atof(splitLine.at(2).c_str())));
			}
			else if(splitLine.at(0) == "vn")
			{
				if(!normalBuffer) normalBuffer = std::make_shared<VertexBuffer>();

				normals.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));
			}
			else if(splitLine.at(0) == "f")
			{
				Face f;

				std::vector<std::string> subsplit;
				splitString(splitLine.at(1), '/', subsplit);

				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.a.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      			f.a.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);

				splitString(splitLine.at(2), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.b.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      			f.b.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);

				splitString(splitLine.at(3), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.c.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
     			f.c.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				faces.push_back(f);

				if(splitLine.size() < 5) continue;
				f = Face();

				splitString(splitLine.at(3), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.a.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      			f.a.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);

				splitString(splitLine.at(4), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.b.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      			f.b.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);

				splitString(splitLine.at(1), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if(texCoordBuffer && subsplit.at(1) != "") texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if(normalBuffer && subsplit.at(2) != "") normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				f.c.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      			f.c.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				faces.push_back(f);
			}
		}

		setBuffer("in_Position", positionBuffer);
		if(texCoordBuffer) 
		{
			setBuffer("in_TexCoord", texCoordBuffer);
		}
		if(normalBuffer) 
		{
			setBuffer("in_Normal", normalBuffer);
		}
	}

	/**
	* Generates vertex array
	*/
	VertexArray::VertexArray() : dirty(false)
	{
		glGenVertexArrays(1, &id);

		if (!id)
		{
			throw Exception("Failed to generate vertex array");
		}

		buffers.resize(10);
	}

	/**
	* Attach a vertex buffer to the vertex array
	*/
	void VertexArray::setBuffer(std::string attribute, std::weak_ptr<VertexBuffer> buffer)
	{
		if (attribute == "in_Position")
		{
			buffers.at(0) = buffer.lock();
			position = buffers.at(0)->getData();
		}
		else if (attribute == "in_Color")
		{
			buffers.at(1) = buffer.lock();
			color = buffers.at(1)->getData();
		}
		else if (attribute == "in_TexCoord")
		{
			buffers.at(2) = buffer.lock();
			texCoord = buffers.at(2)->getData();
		}
		else if(attribute == "in_Normal")
		{
			buffers.at(3) = buffer.lock();
			normal = buffers.at(3)->getData();
		}
		else
		{
			std::string errorMessage = "Failed to set buffer attribute: ";
			errorMessage += attribute;
			throw Exception(errorMessage);
		}

		dirty = true;
	}

	/**
	*Returns vertex count
	*/
	int VertexArray::getVertexCount()
	{
		if (!buffers.at(0))
		{
			throw Exception("Failed to get vertex count");
		}

		return buffers.at(0)->getDataSize() / buffers.at(0)->getNumOfComponents();
	}

	/**
	* Return ID of the vertex array.
	*
	* Sets 'dirty' to false after first draw of new value.
	*/
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

	void VertexArray::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
	{
		std::string curr;

		output.clear();

		for(size_t i = 0; i < input.length(); i++)
		{
			if(input.at(i) == ' ' ||
			input.at(i) == '\r' ||
			input.at(i) == '\n' ||
			input.at(i) == '\t')
			{
			if(curr.length() > 0)
			{
				output.push_back(curr);
				curr = "";
			}
			}
			else
			{
			curr += input.at(i);
			}
		}

		if(curr.length() > 0)
		{
			output.push_back(curr);
		}
	}

	void VertexArray::splitString(std::string& input, char splitter, std::vector<std::string>& output)
	{
		std::string curr;

		output.clear();

		for(size_t i = 0; i < input.length(); i++)
		{
			if(input.at(i) == splitter)
			{
			output.push_back(curr);
			curr = "";
			}
			else
			{
			curr += input.at(i);
			}
		}

		if(curr.length() > 0)
		{
			output.push_back(curr);
		}
	}

	/**
	* Returns positions VertexBuffer
	*/
	std::vector<GLfloat> VertexArray::getPosition()
	{
		return position;
	}

	/**
	* Returns texture co-oridnates VertexBuffer
	*/
	std::vector<GLfloat> VertexArray::getTexCoord()
	{
		return texCoord;
	}

	/**
	* Returns normals VertexBuffer
	*/
	std::vector<GLfloat> VertexArray::getNormal()
	{
		return normal;
	}

	/**
	* Returns color VertexBuffer
	*/
	std::vector<GLfloat> VertexArray::getColor()
	{
		return color;
	}

	std::vector<Face> VertexArray::getFaces()
	{
		return faces;
	}
}