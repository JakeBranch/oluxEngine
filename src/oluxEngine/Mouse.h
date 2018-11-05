#ifndef OLUXENGINE_MOUSE_H
#define OLUXENGINE_MOUSE_H

#include <SDL.h>
#include <glm/glm.hpp>

namespace OluxEngine
{
    class Mouse
    {
        public:
        Mouse();

        void update();
        glm::vec2 getPosition();

        private:
        int x;
        int y;
        glm::vec2 position;
    };
}

#endif