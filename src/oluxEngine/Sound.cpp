#include "Sound.h"

namespace OluxEngine
{
    Sound::Sound() { }

    /**
    * Loads sound data, creates sound buffer, and returns reference to buffer
    */
    std::shared_ptr<Sound> Sound::Load(std::string path)
    {
        std::shared_ptr<Sound> rtn = std::make_shared<Sound>();

        ALenum format = 0;
        ALsizei freq = 0;
        std::vector<char> bufferData;

        alGenBuffers(1, &rtn->id);

        rtn->loadOGG(path.c_str(), bufferData, format, freq);

        alBufferData(rtn->id, format, &bufferData[0],
            static_cast<ALsizei>(bufferData.size()), freq);

        return rtn;
    }

    /**
    * Plays sound
    */ 
    void Sound::play()
    {
        ALuint sid = 0;
        alGenSources(1, &sid);
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);

        alSourcei(sid, AL_BUFFER, id);
        alSourcePlay(sid);
    }

    void Sound::play(float vol, float varMin, float varMax)
    {
        varMin*=1000.0f;
        varMax*=1000.0f;
        float variance = (std::rand() % ((int)varMin + 1 - (int)varMax) + (int)varMin)/1000.0f;
        ALuint sid = 0;
        alGenSources(1, &sid);
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSourcei(sid, AL_BUFFER, id);
        alSourcef(sid, AL_PITCH, variance);
        alSourcef(sid, AL_GAIN, vol);
        alSourcePlay(sid);
    }

    /**
    * Loads OGG file
    */
    void Sound::loadOGG(std::string fileName, std::vector<char> &buffer,
                ALenum &format, ALsizei &freq)
    {
        int endian = 0;
        int bitStream = 0;
        long bytes = 0;
        char array[2048] = {0};
        vorbis_info *pInfo = NULL;
        OggVorbis_File oggFile = {0};

        if(ov_fopen(fileName.c_str(), &oggFile) != 0)
        {
            std::cout << "Failed to open file '" << fileName << "' for decoding" << std::endl;
        
            std::string errorMessage = "Failed to open file: ";
			errorMessage += fileName;
			throw Exception(errorMessage);
        }

        pInfo = ov_info(&oggFile, -1);

        if(pInfo->channels == 1)
        {
        format = AL_FORMAT_MONO16;
        }
        else
        {
        format = AL_FORMAT_STEREO16;
        }

        freq = pInfo->rate;

        while(true)
        {
 
        bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

        if(bytes < 0)
        {
            ov_clear(&oggFile);
    
            std::string errorMessage = "Failed to decode file: ";
			errorMessage += fileName;
			throw Exception(errorMessage);
        }
        else if(bytes == 0)
        {
            break;
        }

        buffer.insert(buffer.end(), array, array + bytes);
        }

        ov_clear(&oggFile);
    }

    /**
    * Deletes buffer upon destruction
    */
    Sound::~Sound()
    {
        alDeleteBuffers(1, &id);
    }

}