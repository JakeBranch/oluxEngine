#include "Keyboard.h"

#include <iostream>

namespace OluxEngine
{
    Keyboard::Keyboard()
    {

    }

    bool Keyboard::getKeyDown(SDL_Scancode scanCode)
    {
        return keyboardStates[scanCode];
    }

    void Keyboard::update()
    {
        keyboardStates = SDL_GetKeyboardState(NULL);
    }
}