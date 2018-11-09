#include <SDL.h>

#include <memory>
#include <vector>

#include <GL\glew.h>

#include "Resources.h"

#include <cstdio>
#include <ctime>

#include <AL/al.h>
#include <AL/alc.h>

#include "Exception.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <glm/glm.hpp>

namespace OluxEngine
{
	class Entity;
	
	/**
	*Core engine class. Handles initialisation, game loop, entity management, and stores references to environment variables.
	*/
	class Core
	{
		public:
			static std::shared_ptr<Core> initialise();

			void Start();
			void Stop();
			std::shared_ptr<Entity> addEntity();

			std::shared_ptr<Resources> getResources();
			std::shared_ptr<Camera> getCamera();
			std::shared_ptr<Keyboard> getKeyboard();
			std::shared_ptr<Mouse> getMouse();

		private:
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::weak_ptr<Core> self;
			std::shared_ptr <Resources> resourceManager;
			std::shared_ptr<Camera> camera;
			std::shared_ptr<Keyboard> keyboard;
			std::shared_ptr<Mouse> mouse;

			clock_t clockStart;
			double timer;

			SDL_Window *window;

			ALCdevice* device;
  			ALCcontext* context;
	};
}