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

	std::shared_ptr<ShaderProgram> ShaderProgram::Load(const char* vertLoc, const char* fragLoc)
	{		
		std::ifstream fileStream(vertLoc, std::ios::in);
		std::string vertSrc;

		if (!fileStream.is_open())
		{
			std::string errorMessage = "Failed to open shader file: ";
			errorMessage += vertLoc;
			throw Exception(errorMessage);
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			vertSrc.append(line + "\n");
		}

		fileStream.close();

		fileStream.open(fragLoc, std::ios::in);
		std::string fragSrc;

		if (!fileStream.is_open())
		{
			std::string errorMessage = "Failed to open shader file: ";
			errorMessage += fragLoc;
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

		std::shared_ptr<ShaderProgram> rtn = Create(vertCode, fragCode, vertLoc, fragLoc);

		return rtn;
	}

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

    void ShaderProgram::Draw(VertexArray& vertexArray)
    {
        glUseProgram(id);
        glBindVertexArray(vertexArray.getId());

		for(size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if(samplers.at(i).texture)
			{
				glBindTexture(GL_TEXTURE_2D, samplers.at(i).texture->getId());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

        glDrawArrays(GL_TRIANGLES, 0, vertexArray.getVertexCount());

		for(size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

        glBindVertexArray(0);
        glUseProgram(0);
    }

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
		samplers.push_back(s);

		glUseProgram(id);
		glUniform1i(uniformId, samplers.size() - 1);
		glUseProgram(0);
	}

    GLuint ShaderProgram::getId()
    {
        return id;
    }
}