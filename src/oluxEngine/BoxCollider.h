#ifndef OLUXENGINE_BOXCOLLIDER_H
#define OLUXENGINE_BOXCOLLIDER_H

#include "Component.h"

#include <glm/glm.hpp>

namespace OluxEngine 
{
    /**
    * class to handle box-box collision
    */
    class BoxCollider : public Component
    {
        public:
            void onInit();
            bool isColliding(glm::vec3 playerPos, glm::vec3 objPos, glm::vec3 objSize);
    };
}

#endif