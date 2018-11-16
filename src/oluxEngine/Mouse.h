#ifndef OLUXENGINE_MOUSE_H
#define OLUXENGINE_MOUSE_H

#include <SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#define MOUSE_LEFT 0

namespace OluxEngine
{
    /**
    * Class to handle mouse events
    */
    class Mouse
    {
        public:
        Mouse();

        void updatePosition(int x, int y);
        glm::vec2 getPosition();

        void setButtonDown(int button);
        void setButtonUp(int button);

        bool getMouseButtonDown(int button);
        bool getMouseButtonUp(int button);

        private:
        /**
        * Position of mouse
        */
        glm::vec2 position;

        std::vector<int> mouseButtons;
        std::vector<int> upMouseButtons;
        std::vector<int> downMouseButtons;
    };
}

#endif