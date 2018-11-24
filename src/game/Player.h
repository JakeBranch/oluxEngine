#include <oluxEngine\OluxEngine.h>

#include "Environment.h"

#include <string>
#include <list>

#include <SDL.h>
#include <glm/glm.hpp>

class Player : public OluxEngine::Component
{
	public:
		void onInit(std::string meshLoc, std::string textureLoc);
		void onBegin();
		void onUpdate();

        std::shared_ptr<OluxEngine::StaticModelCollider> smc;

		glm::vec3 size;

		float speed;

		//todo - move to environment
		double lastTime;
		float deltaTime;
};