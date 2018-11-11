#include "Light.h"

namespace OluxEngine
{
    Light::Light()
    {
        ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
        specular = glm::vec3(0.5f, 0.5f, 0.5f);
    }

    glm::vec3 Light::getAmbient()
    {
        return ambient;
    }

    glm::vec3 Light::getDiffuse()
    {
        return diffuse;
    }

    glm::vec3 Light::getSpecular()
    {
        return specular;
    }

    void Light::setAmbient(glm::vec3 val)
    {
        ambient = val;
    }

    void Light::setDiffuse(glm::vec3 val)
    {
        diffuse = val;
    }

    void Light::setSpecular(glm::vec3 val)
    {
        specular = val;
    }
}