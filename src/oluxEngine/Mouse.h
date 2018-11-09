#ifndef OLUXENGINE_MOUSE_H
#define OLUXENGINE_MOUSE_H

#include <SDL.h>
#include <glm/glm.hpp>

namespace OluxEngine
{
    /**
    * Class to handle mouse events
    */
    class Mouse
    {
        public:
        Mouse();

        void update();
        glm::vec2 getPosition();

        private:
        /**
        * X position of mouse
        */ 
        int x;

        /**
        * Y position of mouse
        */ 
        int y;

        /**
        * Position of mouse
        */
        glm::vec2 position;
    };
}

#endif