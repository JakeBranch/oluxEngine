#ifndef OLUXENGINE_DIRECTIONALLIGHT_H
#define OLUXENGINE_DIRECTIONALLIGHT_H

#include "Light.h"

namespace OluxEngine
{
    /**
	*Class to hold directional light properties
	*/
	class DirectionalLight : public Light
    {
        public:
            DirectionalLight();

            glm::vec3 getDirection();

        private:
            glm::vec3 direction;
    };
}

#endif
