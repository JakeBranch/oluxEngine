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
		rtn->postProcessing = true;
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
		rtn->postProcessor = std::make_shared<PostProcessor>(rtn);
		rtn->gui = std::make_shared<Gui>(rtn);
		
		return rtn;
	}

	/**
	* Starts game loop. Handles updating and drawing of entities and environment variables
	*/
	void Core::start()
	{
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
				else if(event.type == SDL_MOUSEMOTION)
				{
					mouse->updatePosition(event.motion.x, event.motion.y);
				}
				else if(event.type == SDL_MOUSEBUTTONDOWN)
				{
					mouse->setButtonDown(event.button.button);
				}
				else if(event.type == SDL_MOUSEBUTTONUP)
				{
					mouse->setButtonUp(event.button.button);
				}
			}

			onUpdate();

			glEnable(GL_DEPTH_TEST);
			postProcessor->sceneRt->clear();

			if(!postProcessing)
			{
				glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
			
			std::list<std::shared_ptr<Entity>> ces;
			getEntities<Camera>(ces);

			for(std::list<std::shared_ptr<Entity>>::iterator it = ces.begin();
				it != ces.end(); it++)	
			{
				camera = (*it)->getComponent<Camera>();
				
				onDisplay();
			}


			if(postProcessing)
			{
				glDisable(GL_DEPTH_TEST);
				glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

				postProcessor->display();
			}

			onGui();

			SDL_GL_SwapWindow(window);
		}
	}

	/**
	*Propogates update instruction to rest of system
	*/
	void Core::onUpdate()
	{
		keyboard->update();

		for (std::list<std::shared_ptr<Entity>>::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			try
			{
				(*it)->onUpdate();
			}
			catch(Exception& e)
			{
				std::cout << "OluxEngine Exception: " << e.what() << std::endl;
				(*it)->destroy();
			}
		}
		
		for(std::list<std::shared_ptr<Entity>>::iterator it = entities.begin(); 
			it != entities.end();)
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

	/**
	*Propogates display instruction to rest of system
	*/
	void Core::onDisplay()
	{
		for (std::list<std::shared_ptr<Entity>>::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			try
			{
				(*it)->onDisplay();
			}
			catch(Exception& e)
			{
				std::cout << "OluxEngine Exception: " << e.what() << std::endl;
				(*it)->destroy();
			}
		}
	}

	/**
	*Propogates gui instruction to rest of system
	*/
	void Core::onGui()
	{
		for (std::list<std::shared_ptr<Entity>>::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			try
			{
				(*it)->onGui();
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
	void Core::stop()
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

	std::shared_ptr<Mouse> Core::getMouse()
	{
		return mouse;
	}

	/**
	*Creates, stores, and returns an entity
	*/
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->self = rtn;
		rtn->core = self;
		entities.push_back(rtn);

		return rtn;
	}

	/**
	*returns if post processing is enabled
	*/
	bool Core::postProcessingEnabled()
	{
		return postProcessing;
	}

	/**
	*returns reference to post processor
	*/
	std::shared_ptr<PostProcessor> Core::getPostProcessor()
	{
		return postProcessor;
	}

	/**
	*returns reference to GUI
	*/
	std::shared_ptr<Gui> Core::getGui()
	{
		return gui;
	}

	/**
	*Removes all entities from memory
	*/
	void Core::clearWorld()
	{
		for (std::list<std::shared_ptr<Entity>>::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			(*it)->destroy();
		}
	}
}