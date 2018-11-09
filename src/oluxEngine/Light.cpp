#include "Light.h"

namespace OluxEngine
{
    Light::Light()
    {
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        ambientIntensity = 1.0f;
    }
}