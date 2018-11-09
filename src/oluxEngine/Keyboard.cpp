#include "Keyboard.h"

#include <iostream>

namespace OluxEngine
{
    Keyboard::Keyboard()
    {

    }

    /**
    * Returns if key is down
    */
    bool Keyboard::getKeyDown(SDL_Scancode scanCode)
    {
        return keyboardStates[scanCode];
    }

    /**
    * Updates key states
    */
    void Keyboard::update()
    {
        keyboardStates = SDL_GetKeyboardState(NULL);
    }
}