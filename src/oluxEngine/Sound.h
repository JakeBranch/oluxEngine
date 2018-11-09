#include "Resource.h"

#include <memory>
#include <string>

#include <iostream>
#include <vector>

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include "Exception.h"

namespace OluxEngine
{
    /**
    * Class to handle the loading and creation of sound effects.
    */
    class Sound : public Resource
    {
        /**
        * ID of the sound effect
        */
        ALuint id;

        void loadOGG(std::string fileName, std::vector<char> &buffer,
            ALenum &format, ALsizei &freq);

        public:
            Sound();
            ~Sound();

            static std::shared_ptr<Sound> Load(std::string path);

            void play(float vol, float varMin, float varMax);
            void play();
    };

}