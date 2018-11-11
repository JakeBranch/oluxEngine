#ifndef OLUXENGINE_SPOTLIGHT_H
#define OLUXENGINE_SPOTLIGHT_H

#include "Light.h"

namespace OluxEngine
{
	class SpotLight : public Light
    {
        public:
            SpotLight();

            glm::vec3 getPosition();
            glm::vec3 getDirection();
            
            GLfloat getConstant();
            GLfloat getLinear();
            GLfloat getQuadratic();

            GLfloat getCutoff();
            GLfloat getOuterCutoff();

            void setPosition(glm::vec3 val);
            void setDirection(glm::vec3 val);
           
        private:
            glm::vec3 position;
            glm::vec3 direction;

            GLfloat cutoff;
            GLfloat outerCutoff;

            GLfloat constant;
            GLfloat linear;
            GLfloat quadratic;
    };
}

#endif