#ifndef OLUXENGINE_POINTLIGHT_H
#define OLUXENGINE_POINTLIGHT_H

#include "Light.h"

namespace OluxEngine
{
	class PointLight : public Light
    {
        public:
            PointLight();

            glm::vec3 getPosition();
            GLfloat getConstant();
            GLfloat getLinear();
            GLfloat getQuadratic();

            void setPosition(glm::vec3 val);
           
        private:
           glm::vec3 position;
           GLfloat constant;
           GLfloat linear;
           GLfloat quadratic;
    };
}

#endif