#ifndef OLUXENGINE_MATERIAL_H
#define OLUXENGINE_MATERIAL_H

#include <glm/glm.hpp>

namespace OluxEngine
{
	class Material
	{
        public:
            Material();
            void setAmbient(glm::vec3 val);
            void setDiffuse(glm::vec3 val);
            void setSpecular(glm::vec3 val);
            void setShininess(float val);

            glm::vec3 getAmbient();
            glm::vec3 getDiffuse();
            glm::vec3 getSpecular();
            float getShininess();

        private:
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shininess;
    };
}

#endif