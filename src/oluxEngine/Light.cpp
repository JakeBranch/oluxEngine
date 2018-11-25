#include "Light.h"

namespace OluxEngine
{
    /**
    *Initialise light properties
    */
    void Light::onInit()
    {
        ambient = glm::vec3(0.05f, 0.05f, 0.05f);
        diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
        specular = glm::vec3(0.5f, 0.5f, 0.5f);

        ambientIntensity = 0.2;

        color = glm::vec3(1.0f, 1.0f, 1.0f);
        setAmbient(glm::vec3(getColor().x * ambientIntensity, getColor().y * ambientIntensity, getColor().z * ambientIntensity));
        setDiffuse(glm::vec3(getColor().x, getColor().y, getColor().z));
        setSpecular(glm::vec3(getColor().x, getColor().y, getColor().z));
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
    
    glm::vec3 Light::getColor()
    {
        return color;
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

    void Light::setColor(glm::vec3 val)
    {
        color = val;

        setAmbient(glm::vec3(getColor().x * ambientIntensity, getColor().y * ambientIntensity, getColor().z * ambientIntensity));
        setDiffuse(glm::vec3(getColor().x, getColor().y, getColor().z));
        setSpecular(glm::vec3(getColor().x, getColor().y, getColor().z));
    }

    void Light::setAmbientIntensity(float val)
    {
        ambientIntensity = val;
        setAmbient(glm::vec3(getColor().x * ambientIntensity, getColor().y * ambientIntensity, getColor().z * ambientIntensity));
    }
}