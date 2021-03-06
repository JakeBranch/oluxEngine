#include "Transform.h"
#include <iostream>

namespace OluxEngine
{
	void Transform::onInit()
	{
        localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        localRotation = glm::vec3(0.0f, 0.0f, 0.0f);
        localScale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    glm::vec3 Transform::getPosition()
    {
        return localPosition;
    }

    glm::vec3 Transform::getRotation()
    {
        return localRotation;
    }

    glm::vec3 Transform::getScale()
    {
        return localScale;
    }

    void Transform::setLocalPosition(glm::vec3 val)
    {
        localPosition = val;
    }

    void Transform::setLocalRotation(glm::vec3 val)
    {
        localRotation = val;
    }

    void Transform::setLocalScale(glm::vec3 val)
    {
        localScale = val;
    }

    void Transform::translate(glm::vec3 val)
    {
        localPosition.x += val.x;
        localPosition.y += val.y;
        localPosition.z += val.z;
    }

    void Transform::rotate(glm::vec3 val)
    {
        localRotation.x += val.x;
        localRotation.y += val.y;
        localRotation.z += val.z;
    }

    void Transform::scale(glm::vec3 val)
    {
        localScale.x += val.x;
        localScale.y += val.y;
        localScale.z += val.z;
    }

    glm::mat4 Transform::getModelMatrix()
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, localPosition);

        model = glm::rotate(model, glm::radians(localRotation.z), glm::vec3(0, 0, 1));
        model = glm::rotate(model, glm::radians(localRotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(localRotation.x), glm::vec3(1, 0, 0));

        model = glm::scale(model, localScale);

        return model;
    }
}