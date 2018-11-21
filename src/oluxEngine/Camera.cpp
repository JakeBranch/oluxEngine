#include "Camera.h"

namespace OluxEngine
{
    void Camera::onInit()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = 0.0f;
        pitch = 0.0f; 
        front = glm::vec3(0.0f, 0.0f, -1.0f);

        getEntity()->addComponent<Transform>();
    }

    /**
    * Calculate and return view matrix
    */
    glm::mat4 Camera::getViewMatrix()
    {
        // return glm::lookAt(position, position + front, up);

        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), getEntity()->getComponent<Transform>()->getPosition()); //getCore()->getCamera()->getViewMatrix();

		// viewMatrix = glm::rotate(viewMatrix, glm::radians(cameraTransform->getRotation().x), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(getEntity()->getComponent<Transform>()->getRotation().y), glm::vec3(0, 1, 0));
		// viewMatrix = glm::rotate(viewMatrix, glm::radians(cameraTransform->getRotation().z), glm::vec3(0, 0, 1));
		viewMatrix = glm::inverse(viewMatrix);
        return viewMatrix;
    }

    /**
    * Update camera properties
    */ 
    void Camera::update()
    {
        // yaw += 0.25f;
        front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));	
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    void Camera::setPosition(glm::vec3 val)
    {
        position = val;
    }

    void Camera::setRotation(glm::vec3 val)
    {
        pitch = val.x;
        yaw = val.y;
    }

    glm::vec3 Camera::getPosition()
    {
        return position;
    }
}