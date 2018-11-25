#ifndef OLUXENGINE_CAMERA_H
#define OLUXENGINE_CAMERA_H

#include "Component.h"
#include "Transform.h"
#include "Entity.h"

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
            void onInit();

            glm::mat4 getViewMatrix();
    };
}

#endif