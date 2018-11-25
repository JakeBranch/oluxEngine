#include "Camera.h"

namespace OluxEngine
{
    /**
    * Initialise camera properties
    */
    void Camera::onInit()
    {
        getEntity()->addComponent<Transform>();
    }

    /**
    * Calculate and return view matrix
    */
    glm::mat4 Camera::getViewMatrix()
    {
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), getEntity()->getComponent<Transform>()->getPosition());

		viewMatrix = glm::rotate(viewMatrix, glm::radians(getEntity()->getComponent<Transform>()->getRotation().x), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(getEntity()->getComponent<Transform>()->getRotation().y), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(getEntity()->getComponent<Transform>()->getRotation().z), glm::vec3(0, 0, 1));
		viewMatrix = glm::inverse(viewMatrix);
        return viewMatrix;
    }
}