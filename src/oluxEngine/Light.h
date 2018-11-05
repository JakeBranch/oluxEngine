#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OluxEngine
{
    class Light : public Component
    {
        public:
            Light();
            Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);
            void onInit();

            void UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc);
        private:
            glm::vec3 color;
            GLfloat ambientIntensity;
    };
}