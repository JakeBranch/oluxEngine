#include "Core.h"
#include "Entity.h"
#include <iostream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

namespace OluxEngine
{
	/**
	*Returns a shared pointer to <Core>, Initialises SDL/OpenGL, initialises OpenAL, initialises environment objects
	*/
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
		rtn->keyboard = std::make_shared<Keyboard>();
		rtn->mouse = std::make_shared<Mouse>();

		return rtn;
	}

	/**
	* Starts game loop. Handles updating and drawing of entities and environment variables
	*/
	void Core::Start()
	{
		bool test = true;
		int tick = 0;
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
				else if(event.type == SDL_KEYDOWN)
				{
					std::cout << "KeyDown: " << event.key.keysym.sym << std::endl;
				}
				else if(event.type == SDL_KEYUP)
				{
					std::cout << "----------------------------------------" << std::endl;
					std::cout << "KeyUp: " << event.key.keysym.sym << std::endl;
					std::cout << "----------------------------------------" << std::endl;
				}
			}

			update();

			std::vector<std::shared_ptr<Entity>> ces;
			getEntities<Camera>(ces);

			glEnable(GL_DEPTH_TEST);

			glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for(size_t i = 0; i < ces.size(); i++)
			{
				camera = ces.at(i)->getComponent<Camera>();
	
				if(test)
				{
					glViewport(0, 0, (GLsizei)(300), (GLsizei)(800));
					test = false;
				}
				else
				{
					glViewport(300, 0, (GLsizei)(300), (GLsizei)(800));
					test = true;
				}

				display();
			}

			SDL_GL_SwapWindow(window);
		}
	}

	void Core::update()
	{
		keyboard->update();
		mouse->update();

		if(keyboard->getKeyDown(SDL_SCANCODE_W))
		{
			std::cout << "W" << std::endl;
		}

		if(camera)
			camera->update();

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

		//--------------------------------------------------UPDATE RESOURCES
		timer = ( clock() - clockStart ) / (double) CLOCKS_PER_SEC;

		if(timer >= 2)
		{
			resourceManager->cleanUp();
			
			clockStart = clock();
		}
	}

	void Core::display()
	{
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
	}

	/**
	*Stops application
	*/
	void Core::Stop()
	{
		running = false;
	}

	/**
	*Returns resourceManager object
	*/
	std::shared_ptr<Resources> Core::getResources()
	{
		return resourceManager;
	}

	/**
	*Returns camera objecet
	*/
	std::shared_ptr<Camera> Core::getCamera()
	{
		return camera;
	}

	/**
	*Returns keyboard object
	*/
	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return keyboard;
	}

	/**
	*Creates, stores, and returns an entity
	*/
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		entities.push_back(rtn);
		rtn->self = rtn;
		rtn->core = self;

		return rtn;
	}
}