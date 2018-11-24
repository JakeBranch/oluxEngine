#include "DirectionalLight.h"

namespace OluxEngine
{
    DirectionalLight::DirectionalLight()
    {
        setAmbientIntensity(0.01f);
        direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    }

    glm::vec3 DirectionalLight::getDirection()
    {
        return direction;
    }
}