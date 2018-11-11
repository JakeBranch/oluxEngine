#include "SpotLight.h"

namespace OluxEngine
{
    SpotLight::SpotLight()
    {
        setAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
        setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
        setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

        position = glm::vec3(0.0f, 0.0f, 0.0f);
        direction = glm::vec3(0.0f, 0.0f, -1.0f);

        constant = 1.0f;
        linear = 0.014f;
        quadratic = 0.0007f;

        cutoff = glm::cos(glm::radians(12.5f));
        outerCutoff = glm::cos(glm::radians(15.0f));
    }

    glm::vec3 SpotLight::getPosition()
    {
        return position;
    }

    glm::vec3 SpotLight::getDirection()
    {
        return direction;
    }

    GLfloat SpotLight::getConstant()
    {
        return constant;
    }

    GLfloat SpotLight::getLinear()
    {
        return linear;
    }

    GLfloat SpotLight::getQuadratic()
    {
        return quadratic;
    }

    GLfloat SpotLight::getCutoff()
    {
        return cutoff;
    }

    GLfloat SpotLight::getOuterCutoff()
    {
        return outerCutoff;
    }

    void SpotLight::setPosition(glm::vec3 val)
    {
        position = val;
    }
}