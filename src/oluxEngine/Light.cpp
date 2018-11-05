#include "Light.h"

namespace OluxEngine
{
    Light::Light()
    {
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        ambientIntensity = 1.0f;
    }

    Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity)
    {
        color = glm::vec3(red, green, blue);
        ambientIntensity = ambientIntensity;
    }

	void Light::onInit()
	{

    }

    void Light::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc)
    {
        glUniform3f(ambientColorLoc, color.x, color.y, color.z);
        glUniform1f(ambientIntensityLoc, ambientIntensity);
    }
}