#include "PointLight.h"

namespace OluxEngine
{
    /**
	*initialise point light properties
	*/
    PointLight::PointLight()
    {
        position = glm::vec3(0.0f, 0.0f, -5.0f);
        
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