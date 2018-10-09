#include "ShaderProgram.h"
#include "VertexArray.h"

#include "ext.hpp"

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
			throw std::exception();
			std::cout << "COMPILE STATUS" << std::endl;
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
			throw std::exception();
			std::cout << "COMPILE STATUS" << std::endl;
		}

		glAttachShader(rtn->id, fragShader);

		glLinkProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_LINK_STATUS, &result);
		if (!result)
		{
			throw std::exception();
			std::cout << "GL_LINK_STATUS" << std::endl;
		}

		glValidateProgram(rtn->id);
		glGetProgramiv(rtn->id, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			throw std::exception();
			std::cout << "GL_VALIDATE_STATUS" << std::endl;
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
            printf("Error creating shader program");
            throw std::exception();
        }

        AddShader(id, vertCode, GL_VERTEX_SHADER);
        AddShader(id, fragCode, GL_FRAGMENT_SHADER);

        GLint result = 0;

        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        if (!result)
        {       
            throw std::exception();
             std::cout << "GL_LINK_STATUS" << std::endl;
        }

        glValidateProgram(id);
        glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
            throw std::exception();
             std::cout << "GL_VALIDATE_STATUS" << std::endl;
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
            throw std::exception();
             std::cout << "COMPILE STATUS" << std::endl;
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

    GLuint ShaderProgram::getId()
    {
        return id;
    }
}