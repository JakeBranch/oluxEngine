#ifndef OLUXENGINE_LIGHT_H
#define OLUXENGINE_LIGHT_H

#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OluxEngine
{
    class Light
    {
        public:
            Light();

        private:
            glm::vec3 position;
            glm::vec3 color;

            GLfloat ambientIntensity;
    };
}

#endif