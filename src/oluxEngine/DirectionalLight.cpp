#include "DirectionalLight.h"

namespace OluxEngine
{
    DirectionalLight::DirectionalLight()
    {
        setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
        setDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
        setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

        direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    }

    glm::vec3 DirectionalLight::getDirection()
    {
        return direction;
    }
}