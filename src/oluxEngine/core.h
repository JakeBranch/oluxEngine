#ifndef OLUXENGINE_CORE_H
#define OLUXENGINE_CORE_H

#include <SDL.h>

#include <memory>
#include <vector>

#include <GL\glew.h>

#include "Resources.h"

#include <cstdio>
#include <ctime>

#include <AL/al.h>
#include <AL/alc.h>

#include "Entity.h"

#include "Exception.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "PostProcessor.h"
#include "Gui.h"

#include <glm/glm.hpp>

namespace OluxEngine
{	
	/**
	*Core engine class. Handles initialisation, game loop, entity management, and stores references to environment variables.
	*/
	class Core
	{
		public:
			static std::shared_ptr<Core> initialise();

			void Start();
			void Stop();

			void update();
			void display();
			void onGui();

			std::shared_ptr<Entity> addEntity();

			template <typename T>
			std::shared_ptr<Entity> getEntity()
			{
				for (std::vector<std::shared_ptr<Entity> > ::iterator it = entities.begin();
				it != entities.end(); it++)
				{
					if(!(*it)->getAlive()) continue;

					if((*it)->hasComponent<T>())
					{
						return *it;
					}
				}

				throw Exception("Failed to retrieve entity with specified type");
			}

			template <typename T>
			void getEntities(std::vector<std::shared_ptr<Entity>> &found)
			{
				for(std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
					it != entities.end(); it++)	
				{
					if(!(*it)->getAlive()) continue;

					if((*it)->hasComponent<T>())
					{
						found.push_back(*it);
					}
				}
			}

			std::shared_ptr<Resources> getResources();
			std::shared_ptr<Camera> getCamera();
			std::shared_ptr<Keyboard> getKeyboard();
			std::shared_ptr<Mouse> getMouse();

			bool postProcessingEnabled();

			std::shared_ptr<PostProcessor> getPostProcessor();
			std::shared_ptr<Gui> getGui();

		private:
			bool running;
			bool postProcessing;
			std::vector<std::shared_ptr<Entity>> entities;
			std::weak_ptr<Core> self;
			std::shared_ptr <Resources> resourceManager;
			std::shared_ptr<Camera> camera;
			std::shared_ptr<Keyboard> keyboard;
			std::shared_ptr<Mouse> mouse;
			std::shared_ptr<PostProcessor> postProcessor;
			std::shared_ptr<Gui> gui;

			clock_t clockStart;
			double timer;

			SDL_Window *window;

			ALCdevice* device;
  			ALCcontext* context;
	};
}

#endif 