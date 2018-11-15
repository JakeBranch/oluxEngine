#ifndef OLUXENGINE_CAMERA_H
#define OLUXENGINE_CAMERA_H

#include "Component.h"

#include <memory>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace OluxEngine
{
    /**
    * Class to manage camera properties 
    */
    class Camera : public Component
    {
        public:
            glm::mat4 getViewMatrix();

            Camera();
            void update();

            void setPosition(glm::vec3 val);
            void setRotation(glm::vec3 val);
            glm::vec3 getPosition();
        private:
            glm::vec3 position;
            glm::vec3 front;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 worldUp;

            GLfloat yaw;
            GLfloat pitch;

            // GLfloat moveSpeed;
            // GLfloat turnSpeed;
    };
}

#endif