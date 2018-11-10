#include "Camera.h"

namespace OluxEngine
{
    /**
    * Initialise camera properties
    */
    Camera::Camera()
    {
        position = glm::vec3(0.0f, 5.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch = -15.0f;
        front = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    /**
    * Calculate and return view matrix
    */
    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    /**
    * Update camera properties
    */ 
    void Camera::update()
    {
        yaw += 0.25f;
        front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));	
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::vec3 Camera::getPosition()
    {
        return position;
    }
}