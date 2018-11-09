#include "Material.h"

namespace OluxEngine
{
    Material::Material()
    {
        ambient = glm::vec3(1.0f, 1.0f, 1.0f);
        diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        specular = glm::vec3(1.0f, 1.0f, 1.0f);
        shininess = 1;
    }

    void Material::setAmbient(glm::vec3 val)
    {
        ambient = val;
    }

    void Material::setDiffuse(glm::vec3 val)
    {
        diffuse = val;
    }

    void Material::setSpecular(glm::vec3 val)
    {
        specular = val;
    }

    void Material::setShininess(float val)
    {
        shininess = val;
    }

    glm::vec3 Material::getAmbient()
    {
        return ambient;
    }

    glm::vec3 Material::getDiffuse()
    {
        return diffuse;
    }

    glm::vec3 Material::getSpecular()
    {
        return specular;
    }

    float Material::getShininess()
    {
        return shininess;
    }
}