#include <SDL.h>

#include <memory>
#include <vector>

#include <GL\glew.h>

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

		private:
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::weak_ptr<Core> self;

			SDL_Window *window;
	};
}