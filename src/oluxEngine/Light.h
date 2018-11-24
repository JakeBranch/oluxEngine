#ifndef OLUXENGINE_LIGHT_H
#define OLUXENGINE_LIGHT_H

#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

namespace OluxEngine
{
    class Light : public Component
    {
        public:
            void onInit();

            glm::vec3 getAmbient();
            glm::vec3 getDiffuse();
            glm::vec3 getSpecular();
            glm::vec3 getColor();

            void setAmbient(glm::vec3 val);
            void setDiffuse(glm::vec3 val);
            void setSpecular(glm::vec3 val);
            void setColor(glm::vec3 val);
            void setAmbientIntensity(float val);

        private:
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            glm::vec3 color;

            GLfloat ambientIntensity;
    };
}

#endif