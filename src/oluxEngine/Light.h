#ifndef OLUXENGINE_LIGHT_H
#define OLUXENGINE_LIGHT_H

#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

namespace OluxEngine
{
    class Light
    {
        public:
            Light();

            glm::vec3 getAmbient();
            glm::vec3 getDiffuse();
            glm::vec3 getSpecular();

            void setAmbient(glm::vec3 val);
            void setDiffuse(glm::vec3 val);
            void setSpecular(glm::vec3 val);

            std::string getType();
        private:
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;

            std::string type;
    };
}

#endif