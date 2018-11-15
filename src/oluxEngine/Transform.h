#ifndef OLUXENGINE_TRANSFORM_H
#define OLUXENGINE_TRANSFORM_H

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace OluxEngine
{
    class Transform : public Component
    {
        public:
            void onInit();

            void setLocalPosition(glm::vec3 val);
            void setLocalRotation(glm::vec3 val);
            void setLocalScale(glm::vec3 val);

            void translate(glm::vec3 val);
            void rotate(glm::vec3 val);
            void scale(glm::vec3 val);

            glm::mat4 getModelMatrix();

        private:
            glm::vec3 localPosition;
            glm::vec3 localRotation;
            glm::vec3 localScale;
    };
}

#endif