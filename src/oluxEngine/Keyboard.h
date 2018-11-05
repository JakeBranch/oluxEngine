#ifndef OLUXENGINE_KEYBOARD_H
#define OLUXENGINE_KEYBOARD_H

#include <SDL.h>

namespace OluxEngine
{
    class Keyboard
    {
        public:
        Keyboard();

        bool getKeyDown(SDL_Scancode scanCode);
        void update();

        private:
        const Uint8* keyboardStates;
    };
}

#endif