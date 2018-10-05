#include <oluxEngine/OluxEngine.h>
#include <glm.hpp>

#include <cstdio>
#include <iostream>
#include <memory>

#include <exception>

#include <GL\glew.h>

#include <SDL.h>

#include <SDL_opengl.h>

#include "TestScene.h"

const GLchar *vertexShaderSrc =
"attribute vec3 in_Position;				" \
"											" \
"void main()								" \
"{											" \
"	gl_Position = vec4(in_Position, 1.0);	" \
"}											";

const GLchar *fragmentShaderSrc =
"void main()								" \
"{											" \
"	gl_FragColor = vec4(0, 0, 1, 1);		" \
"}											";

const GLint WIDTH = 800, HEIGHT = 600;

const GLfloat positions[] = {
0.0f, 0.5f, 0.0f,
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f
};

int main(int argc, char* argv[])
{
	std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

	std::shared_ptr<OluxEngine::Entity> entity = core->addEntity();

	std::shared_ptr<TestScene> ts = entity->addComponent<TestScene>();

	core->Start();

	/*std::cout << "OluxEngine Example game" << std::endl;

	std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();
	//core->Start();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialise");
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	SDL_GLContext sdlContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW");
		return 1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	SDL_Event windowEvent;

	//openGL
	GLuint positionsVboId = 0, VaoId = 0;

	//create a new VBO on GPU and bind it
	glGenBuffers(1, &positionsVboId);
	if (!positionsVboId)
	{
		std::cout << "ERROR1" << std::endl;
		throw std::exception();
	}

	//Create new VAO on the GPU and bind it
	glGenVertexArrays(1, &VaoId);
	if (!VaoId)
	{
		std::cout << "ERROR2" << std::endl;
		throw std::exception();
	}

	glBindVertexArray(VaoId);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	//upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

	glEnableVertexAttribArray(0);

	//reset the state 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR3" << std::endl;
		throw std::exception();
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR4" << std::endl;
		throw std::exception();
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glBindAttribLocation(programId, 0, "in_Position");

	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return 1;
	}

	glValidateProgram(programId);
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(programId, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return 1;
	}

	/*glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		// Clear the colorbuffer
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw OpenGL
		glUseProgram(programId);
		glBindVertexArray(VaoId);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(sdlContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;*/
}