#include "Camera.h"

namespace OluxEngine
{
    Camera::Camera()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch = 0.0f;
        front = glm::vec3(0.0f, 0.0f, -1.0f);

        //moveSpeed = startMoveSpeed;
        //turnSpeed = startTurnSpeed;

        //update();
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    void Camera::update()
    {
        front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));	
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}