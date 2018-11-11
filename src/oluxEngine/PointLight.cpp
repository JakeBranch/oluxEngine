#include "PointLight.h"

namespace OluxEngine
{
    PointLight::PointLight()
    {
        setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
        setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
        setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

        position = glm::vec3(0.0f, 0.0f, -10.0f);
        constant = 1.0f;

        //Distance == 100
        linear = 0.045f;
        quadratic = 0.0075f;

        // Distance == 200
        // linear = 0.22f;
        // quadratic = 0.0019f;

        //Distance == 325
        // linear = 0.014f;
        // quadratic = 0.0007f;

    }

    glm::vec3 PointLight::getPosition()
    {
        return position;
    }

    GLfloat PointLight::getConstant()
    {
        return constant;
    }

    GLfloat PointLight::getLinear()
    {
        return linear;
    }

    GLfloat PointLight::getQuadratic()
    {
        return quadratic;
    }

    void PointLight::setPosition(glm::vec3 val)
    {
        position = val;
    }
}