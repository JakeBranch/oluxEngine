#include <oluxEngine\OluxEngine.h>

#include "Environment.h"

#include <string>

#include <SDL.h>
#include <glm/glm.hpp>

class Player : public OluxEngine::Component
{
	public:
		void onInit(std::string meshLoc);
		void onBegin();
		void update();

        std::shared_ptr<OluxEngine::StaticModelCollider> smc;

		float speed;

		//todo - move to environment
		double lastTime;
		float deltaTime;
};