#include "ShaderProgram.h"
#include "VertexArray.h"

#include <glm/ext.hpp>

#include <fstream>
#include <iostream>
#include <stdio.h>

namespace OluxEngine
{
    ShaderProgram::ShaderProgram()
    {
        
    }

 	/**
    *Reads/Writes shader code from file
    */
	std::shared_ptr<ShaderProgram> ShaderProgram::Load(std::string vertLoc, std::string fragLoc)
	{		
		const char* vertLocation = vertLoc.c_str();
		const char* fragLocation = fragLoc.c_str();
		
		std::ifstream fileStream(vertLocation, std::ios::in);
		std::string vertSrc;

		if (!fileStream.is_open())
		{
			std::string errorMessage = "Failed to open shader file: ";
			errorMessage += vertLocation;
			throw Exception(errorMessage);
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			vertSrc.append(line + "\n");
		}

		fileStream.close();

		fileStream.open(fragLocation, std::ios::in);
		std::string fragSrc;

		if (!fileStream.is_open())
		{
			std::string errorMessage = "Failed to open shader file: ";
			errorMessage += fragLocation;
			throw Exception(errorMessage);
		}

		line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			fragSrc.append(line + "\n");
		}

		fileStream.close();

		const char *vertCode = vertSrc.c_str();
		const char *fragCode = fragSrc.c_str();

		std::shared_ptr<ShaderProgram> rtn = Create(vertCode, fragCode, vertLocation, fragLocation);

		std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
		positions->add(glm::vec2(-1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, 1.0f));

		std::shared_ptr<VertexBuffer> texCoords = std::make_shared<VertexBuffer>();
		texCoords->add(glm::vec2(0.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, 0.0f));

		rtn->simpleShape = std::make_shared<VertexArray>();
		rtn->simpleShape->setBuffer("in_Position", positions);
		rtn->simpleShape->setBuffer("in_TexCoord", texCoords);

		return rtn;
	}

	/**
    *Compiles shaders and creates shader program
    */
	std::shared_ptr<ShaderProgram> ShaderProgram::Create(const char* vertCode, const char* fragCode, const char* vertLoc, const char* fragLoc)
	{
		std::shared_ptr<ShaderProgram> rtn = std::make_shared<ShaderProgram>();

		rtn->id = glCreateProgram();
		if (!rtn->id)
		{
			throw Exception("OpenGL: Failed to create shader program");
		}

		//--------------------------------------Vertex shader
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexCode[1];
		vertexCode[0] = vertCode;

		glShaderSource(vertShader, 1, vertexCode, NULL);
		glCompileShader(vertShader);

		GLint result = 0;

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			GLchar errorLog[1024];
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &errorLog[0]);

			int i = 0;
			while(i <= maxLength)
			{
				std::cout << errorLog[i];
				i++;
			}

			glDeleteShader(vertShader);

			std::string errorMessage = "Failed to compile shader at: ";
			errorMessage += vertLoc;
			throw Exception(errorMessage);
		}

		glAttachShader(rtn->id, vertShader);

		//-------------------------------------Fragment shader
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* fragmentCode[1];
		fragmentCode[0] = fragCode;

		glShaderSource(fragShader, 1, fragmentCode, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			GLchar errorLog[1024];
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);

			int i = 0;
			while(i <= maxLength)
			{
				std::cout << errorLog[i];
				i++;
			}

			glDeleteShader(fragShader);

			std::string errorMessage = "Failed to compile shader at: ";
			errorMessage += fragLoc;
			throw Exception(errorMessage);
		}

		glAttachShader(rtn->id, fragShader);

		glBindAttribLocation(rtn->id, 0, "in_Position");
		glBindAttribLocation(rtn->id, 1, "in_Color");
		glBindAttribLocation(rtn->id, 2, "in_TexCoord");
		glBindAttribLocation(rtn->id, 3, "in_Normal");

		glLinkProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_LINK_STATUS, &result);
		if (!result)
		{
			throw Exception("OpenGL: Faile to link shader program");
		}

		glValidateProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			throw Exception("OpenGL: Failed to validate shader program");
		}

		return rtn;
	}

	/**
	*Draws the given mesh
	*/
    void ShaderProgram::Draw(std::shared_ptr<VertexArray> vertexArray)
    {
		glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
        glUseProgram(id);
        glBindVertexArray(vertexArray->getId());

		for(size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if(samplers.at(i).isRenderTexture)
			{
				if(samplers.at(i).renderTexture)
				{
					glBindTexture(GL_TEXTURE_2D, samplers.at(i).renderTexture->getId());
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
			else
			{
				if(samplers.at(i).texture)
				{
					glBindTexture(GL_TEXTURE_2D, samplers.at(i).texture->getId());
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
		}

        glDrawArrays(GL_TRIANGLES, 0, vertexArray->getVertexCount());

		for(size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

        glBindVertexArray(0);
        glUseProgram(0);
    }

	void ShaderProgram::Draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderTexture->getFbId());
		glm::vec4 lastViewport = viewport;
		viewport = glm::vec4(0, 0, renderTexture->getSize().x, renderTexture->getSize().y);
		Draw(vertexArray);
		viewport = lastViewport;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShaderProgram::Draw(std::shared_ptr<RenderTexture> renderTexture)
	{
		Draw(renderTexture, simpleShape);
	}

	void ShaderProgram::Draw()
	{
		Draw(simpleShape);
	}

	void ShaderProgram::SetUniform(std::string uniform, std::shared_ptr<RenderTexture> renderTexture)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if(uniformId == -1)
		{
			throw std::exception();
		}

		for(size_t i = 0; i < samplers.size(); i++)
		{
			if(samplers.at(i).id == uniformId)
			{
			samplers.at(i).renderTexture = renderTexture;

			glUseProgram(id);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
			}
		}

		Sampler s;
		s.id = uniformId;
		s.renderTexture = renderTexture;
		s.isRenderTexture = true;
		samplers.push_back(s);

		glUseProgram(id);
		glUniform1i(uniformId, samplers.size() - 1);
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to vec3 value
	*/
	void ShaderProgram::SetUniform(std::string uniform, glm::vec3 value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::string errorMessage = "Failed set uniform value: ";
			errorMessage += uniform;
			throw Exception(errorMessage);
		}

		glUseProgram(id);
		glUniform3f(uniformId, value.x, value.y, value.z);
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to vec4 value
	*/
	void ShaderProgram::SetUniform(std::string uniform, glm::vec4 value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::string errorMessage = "Failed set uniform value: ";
			errorMessage += uniform;
			throw Exception(errorMessage);
		}

		glUseProgram(id);
		glUniform4f(uniformId, value.x, value.y, value.z, value.w);
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to int value
	*/
	void ShaderProgram::SetUniform(std::string uniform, int value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::string errorMessage = "Failed set uniform value: ";
			errorMessage += uniform;
			throw Exception(errorMessage);
		}

		glUseProgram(id);
		glUniform1i(uniformId, value);
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to float value
	*/
	void ShaderProgram::SetUniform(std::string uniform, float value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::string errorMessage = "Failed set uniform value: ";
			errorMessage += uniform;
			throw Exception(errorMessage);
		}

		glUseProgram(id);
		glUniform1f(uniformId, value);
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to mat4 value
	*/
	void ShaderProgram::SetUniform(std::string uniform, glm::mat4 value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::string errorMessage = "Failed set uniform value: ";
			errorMessage += uniform;
			throw Exception(errorMessage);
		}

		glUseProgram(id);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
		glUseProgram(0);
	}

	/**
	*Sets uniform variable to Texture value
	*/
	void ShaderProgram::SetUniform(std::string uniform, std::shared_ptr<Texture> texture)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if(uniformId == -1)
		{
			throw std::exception();
		}

		for(size_t i = 0; i < samplers.size(); i++)
		{
			if(samplers.at(i).id == uniformId)
			{
			samplers.at(i).texture = texture;

			glUseProgram(id);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
			}
		}

		Sampler s;
		s.id = uniformId;
		s.texture = texture;
		s.isRenderTexture = false;
		samplers.push_back(s);

		glUseProgram(id);
		glUniform1i(uniformId, samplers.size() - 1);
		glUseProgram(0);
	}

	/**
	*Returns ID of the shader program
	*/
    GLuint ShaderProgram::getId()
    {
        return id;
    }

	void ShaderProgram::setViewport(glm::vec4 viewport)
	{
		this->viewport = viewport;
	}
}