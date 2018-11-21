#ifndef OLUXENGINE_KEYBOARD_H
#define OLUXENGINE_KEYBOARD_H

#include <SDL.h>
#include <vector>

namespace OluxEngine
{
    /**
    * Class to handle keyboard events
    */
    class Keyboard
    {
        public:
        Keyboard();

        bool getKeyDown(SDL_Scancode scanCode);
        void update();

        private:
        /**
        * Holds current state of keyboard keys
        */
        const Uint8* keyboardStates;
    };
}

#endif