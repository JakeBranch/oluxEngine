#include "Mouse.h"

#include <iostream>

namespace OluxEngine
{
    Mouse::Mouse()
    {

    }

    /**
    * Update mouse position and state
    */
    void Mouse::update()
    {
        SDL_GetMouseState(&x, &y);
        position.x = (float)x;
        position.y = (float)y;
    }

    /**
    * Return mouse position
    */ 
    glm::vec2 Mouse::getPosition()
    {
        return position;
    }
}