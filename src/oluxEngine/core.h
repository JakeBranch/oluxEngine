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

namespace OluxEngine
{
	class Entity;
	
	class Core
	{
		public:
			static std::shared_ptr<Core> initialise();

			void Start();
			void Stop();
			std::shared_ptr<Entity> addEntity();

			std::shared_ptr<Resources> getResources();
			std::shared_ptr<Camera> getCamera();

		private:
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::weak_ptr<Core> self;
			std::shared_ptr <Resources> resourceManager;
			std::shared_ptr<Camera> camera;

			clock_t clockStart;
			double timer;

			SDL_Window *window;

			ALCdevice* device;
  			ALCcontext* context;
	};
}