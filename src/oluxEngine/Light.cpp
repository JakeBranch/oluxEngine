#include "Light.h"

namespace OluxEngine
{
    Light::Light()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        ambientIntensity = 1.0f;
    }

    glm::vec3 Light::getPosition()
    {
        return position;
    }

    glm::vec3 Light::getColor()
    {
        return color;
    }
}