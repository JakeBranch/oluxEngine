#include "Mouse.h"

#include <iostream>

namespace OluxEngine
{
    Mouse::Mouse()
    {

    }

    void Mouse::update()
    {
        SDL_GetMouseState(&x, &y);
        position.x = (float)x;
        position.y = (float)y;
    }

    glm::vec2 Mouse::getPosition()
    {
        return position;
    }
}