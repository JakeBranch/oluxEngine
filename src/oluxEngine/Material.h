#ifndef OLUXENGINE_MATERIAL_H
#define OLUXENGINE_MATERIAL_H

#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"

namespace OluxEngine
{
    class ShaderProgram;

    /**
    *Class to store material properties
    */
	class Material
	{
        public:
            Material();
            void setAmbient(glm::vec3 val);
            void setDiffuse(std::shared_ptr<Texture> tex);
            void setSpecular(glm::vec3 val);
            void setShininess(float val);
            void setShader(std::shared_ptr<ShaderProgram> program);

            glm::vec3 getAmbient();
            std::shared_ptr<Texture> getDiffuse();
            glm::vec3 getSpecular();
            float getShininess();
            std::shared_ptr<ShaderProgram> getShader();


        private:
            glm::vec3 ambient;
            std::shared_ptr<Texture> diffuse;
            glm::vec3 specular;
            float shininess;

            std::shared_ptr<ShaderProgram> shader;
    };
}

#endif