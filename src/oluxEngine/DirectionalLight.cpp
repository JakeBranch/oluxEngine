#include "DirectionalLight.h"

namespace OluxEngine
{
    /**
	*Initialise properties
	*/
    DirectionalLight::DirectionalLight()
    {
        setAmbientIntensity(0.01f);
        direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    }

    /**
	*get light direction
	*/
    glm::vec3 DirectionalLight::getDirection()
    {
        return direction;
    }
}