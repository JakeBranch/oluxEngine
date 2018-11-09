#include "Component.h"

#include <glm/glm.hpp>

namespace OluxEngine
{
    class Transform : public Component
    {
        public:
            void onInit();
            void update();

            void translate(glm::vec3 amount);
            void rotate(glm::vec3 amount);
            void scale(glm::vec3 amount);

            void setLocalPosition(glm::vec3 position);
            void setLocalRotation(glm::vec3 rotation);
            void setLocalScale(glm::vec3 scale);

            glm::vec3 getLocalPosition();
            glm::vec3 getLocalRotation();
            glm::vec3 getLocalScale();

        private:
            glm::vec3 localPosition;
            glm::vec3 localRotation;
            glm::vec3 localScale;
    };
}