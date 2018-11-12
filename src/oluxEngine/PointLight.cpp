#include "PointLight.h"

namespace OluxEngine
{
    PointLight::PointLight()
    {
        position = glm::vec3(0.0f, 0.0f, -5.0f);

        //Distance == 100
        // linear = 0.045f;
        // quadratic = 0.0075f;

        // Distance == 200
        // linear = 0.22f;
        // quadratic = 0.0019f;

        //Distance == 325
        // linear = 0.014f;
        // quadratic = 0.0007f;
        setAmbientIntensity(1.0f);

        linear = 0.07;
        quadratic = 0.017;

        constant = 1.0f;
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