#include "Mouse.h"

#include <iostream>

namespace OluxEngine
{
    Mouse::Mouse()
    {

    }

    void Mouse::updatePosition(int x, int y)
    {
        position.x = x;
        position.y = y;
    }

    bool Mouse::getMouseButtonDown(int button)
    {
        for(int i = 0; i < mouseButtons.size(); i++)
        {
            if(mouseButtons.at(i) == button)
            {
                return false;
            }
        }

        for(int i = 0; i < downMouseButtons.size(); i++)
        {
            if(downMouseButtons.at(i) == button)
            {
                mouseButtons.push_back(button);
                return true;
            }
        }

        return false;
    }

    bool Mouse::getMouseButtonUp(int button)
    {
        for(int i = 0; i < upMouseButtons.size(); i++)
        {
            if(upMouseButtons.at(i) == button)
            {
                return true;
            }
        }

        return false;
    }

    void Mouse::setButtonDown(int button)
    {
        downMouseButtons.push_back(button);

        for(int i = 0; i < upMouseButtons.size(); i++)
        {
            if(upMouseButtons.at(i) == button)
            {
                upMouseButtons.erase(upMouseButtons.begin() + i);
                i--;
            }
        }
    }

    void Mouse::setButtonUp(int button)
    {
        for(int i = 0; i < mouseButtons.size(); i++)
        {
            if(mouseButtons.at(i) == button)
            {
                mouseButtons.erase(mouseButtons.begin() + i);
                i--;
            }
        }

        upMouseButtons.push_back(button);

        for(int i = 0; i < downMouseButtons.size(); i++)
        {
            if(downMouseButtons.at(i) == button)
            {
                downMouseButtons.erase(downMouseButtons.begin() + i);
                i--;
            }
        }
    }

    /**
    * Return mouse position
    */ 
    glm::vec2 Mouse::getPosition()
    {
        return position;
    }
}