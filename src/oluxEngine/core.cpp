#include "Core.h"
#include "Entity.h"
#include <iostream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

namespace OluxEngine
{
	std::shared_ptr<Core> Core::initialise()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->running = true;
		rtn->self = rtn;

		rtn->clockStart = clock();

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw Exception("SDL: Failed to initialise");
		}

		rtn->window = SDL_CreateWindow("OluxEngine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!SDL_GL_CreateContext(rtn->window))
		{
			throw Exception("SDL/OpenGL: Context failed to initialise");
		}

		if (glewInit() != GLEW_OK)
		{
			throw Exception("GLEW: Failed to initialise");
		}

		rtn->device = alcOpenDevice(NULL);

		if(!rtn->device)
		{
			throw Exception("OpenAL: Failed to open audio device");
		}

		rtn->context = alcCreateContext(rtn->device, NULL);

		if(!rtn->context)
		{
			alcCloseDevice(rtn->device);
			throw Exception("OpenAL: Failed to create context");
		}

		if(!alcMakeContextCurrent(rtn->context))
		{
			alcDestroyContext(rtn->context);
			alcCloseDevice(rtn->device);
			throw Exception("OpenAL: Failed to make context current");
		}

		rtn->resourceManager = std::make_shared<Resources>();

		return rtn;
	}

	void Core::Start()
	{
		running = true;
		while (running)
		{
			SDL_Event event = { 0 };

			while (SDL_PollEvent(&event));
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
			}

			//Update all entities
			for (std::vector<std::shared_ptr<Entity> > ::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				try
				{
					(*it)->update();
				}
				catch(Exception& e)
				{
					std::cout << "OluxEngine Exception: " << e.what() << std::endl;
					(*it)->destroy();
				}
			}

			for(auto it = entities.begin(); it != entities.end();)
			{
				if(!(*it)->getAlive())
				{
					it = entities.erase(it);
				}
				else
				{
					it++;
				}
			}

			glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Display all entitites
			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				try
				{
					(*it)->display();
				}
				catch(Exception& e)
				{
					std::cout << "OluxEngine Exception: " << e.what() << std::endl;
					(*it)->destroy();
				}
			}

			SDL_GL_SwapWindow(window);

			//--------------------------------------------------UPDATE RESOURCES
			timer = ( clock() - clockStart ) / (double) CLOCKS_PER_SEC;

			if(timer >= 2)
			{
				std::cout << "CLEAN UP" << std::endl;
				resourceManager->cleanUp();

				clockStart = clock();
			}
		}
	}

	void Core::Stop()
	{
		running = false;
	}

	std::shared_ptr<Resources> Core::getResources()
	{
		return resourceManager;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		entities.push_back(rtn);
		rtn->self = rtn;
		rtn->core = self;

		return rtn;
	}
}