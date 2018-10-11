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
        /*std::string vertString = ReadFile(vertLoc);
        std::string fragString = ReadFile(fragLoc);

        const char *vertSrc = vertString.c_str();
        const char *fragSrc = fragString.c_str();

		CompileShader(vertSrc, fragSrc);*/
    }

	std::shared_ptr<ShaderProgram> ShaderProgram::Load(const char* vertLoc, const char* fragLoc)
	{		
		std::ifstream fileStream(vertLoc, std::ios::in);
		std::string vertSrc;

		if (!fileStream.is_open())
		{
			std::cout << "cant open shader file: " << vertLoc << std::endl;
			throw std::exception();
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
			std::cout << "cant open shader file: " << fragLoc << std::endl;
			throw std::exception();
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

		std::shared_ptr<ShaderProgram> rtn = Create(vertCode, fragCode);

		return rtn;
	}

	std::shared_ptr<ShaderProgram> ShaderProgram::Create(const char* vertCode, const char* fragCode)
	{
		std::shared_ptr<ShaderProgram> rtn = std::make_shared<ShaderProgram>();

		rtn->id = glCreateProgram();
		if (!rtn->id)
		{
			printf("Error creating shader program");
			throw std::exception();
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
			std::cout << " vert COMPILE STATUS" << std::endl;
			throw std::exception();
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

			//std::vector<GLchar> errorLog(maxLength);
			GLchar errorLog[1024];
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);

			//std::cout << errorLog[0] << std::endl;

			int i = 0;
			while(i <= maxLength)
			{
				std::cout << errorLog[i];
				i++;
			}

			glDeleteShader(fragShader);

			std::cout << "frag COMPILE STATUS" << std::endl;
			throw std::exception();
		}

		glAttachShader(rtn->id, fragShader);

		glLinkProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_LINK_STATUS, &result);
		if (!result)
		{
			std::cout << "GL_LINK_STATUS" << std::endl;
			throw std::exception();
		}

		glValidateProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			std::cout << "GL_VALIDATE_STATUS" << std::endl;
			throw std::exception();
		}

		return rtn;
	}

    std::string ShaderProgram::ReadFile(const char* fileLocation)
    {
        std::ifstream fileStream(fileLocation, std::ios::in);
        std::string src;

        if(!fileStream.is_open())
        {
            std::cout << "cant open shader file: " << fileLocation << std::endl;
            throw std::exception();
        }

        std::string line = "";
        while(!fileStream.eof())
        {
            std::getline(fileStream, line);
            src.append(line + "\n");
        }

        fileStream.close();
        return src;
    }

    void ShaderProgram::CompileShader(const char* vertCode, const char* fragCode)
    {
        id = glCreateProgram();

        if(!id)
        {
			std::cout << "Error creating shader program" << std::endl;
            throw std::exception();
        }

        AddShader(id, vertCode, GL_VERTEX_SHADER);
        AddShader(id, fragCode, GL_FRAGMENT_SHADER);

        GLint result = 0;

        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        if (!result)
        {       
			std::cout << "GL_LINK_STATUS" << std::endl;
            throw std::exception();
        }

        glValidateProgram(id);
        glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
			std::cout << "GL_VALIDATE_STATUS" << std::endl;
            throw std::exception();
        }
    }

    void ShaderProgram::AddShader(GLuint program, const char* code, GLenum type)
    {
        GLuint theShader = glCreateShader(type);

        //Possibly change???
        const GLchar* theCode[1];
        theCode[0] = code;
        
        //pass instead of NULL if problems arise
        /*GLint codeLength[1];
        codeLength[0] = strlen(code);*/

        glShaderSource(theShader, 1, theCode, NULL);
        glCompileShader(theShader);

        GLint result = 0;

        glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
        if (!result)
        {
			std::cout << "shader COMPILE STATUS" << std::endl;
            throw std::exception();
        }

        glAttachShader(program, theShader);
    }

    void ShaderProgram::Draw(VertexArray& vertexArray)
    {
        glUseProgram(id);
        glBindVertexArray(vertexArray.getId());

        glDrawArrays(GL_TRIANGLES, 0, vertexArray.getVertexCount());

        glBindVertexArray(0);
        glUseProgram(0);
    }

	void ShaderProgram::SetUniform(std::string uniform, glm::vec4 value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			std::cout << "CANNOT SET UNIFORM: " << uniform << std::endl;
			throw std::exception();
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
			std::cout << "CANNOT SET UNIFORM: " << uniform << std::endl;
			throw std::exception();
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
			std::cout << "CANNOT SET UNIFORM: " << uniform << std::endl;
			throw std::exception();
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
			std::cout << "CANNOT SET UNIFORM: " << uniform << std::endl;
			throw std::exception();
		}

		glUseProgram(id);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
		glUseProgram(0);
	}

    GLuint ShaderProgram::getId()
    {
        return id;
    }
}