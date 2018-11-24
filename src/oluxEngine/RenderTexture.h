#ifndef OLUXENGINE_RENDERTEXTURE_H
#define OLUXENGINE_RENDERTEXTURE_H

#include "Resource.h"
#include "Exception.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

namespace OluxEngine
{
    class RenderTexture : public Resource
    {
        GLuint fbo;
        GLuint texId;
        glm::vec2 size;

        public:
        static std::shared_ptr<RenderTexture> Load(int width, int height);
        // static std::shared_ptr<RenderTexture> Create(unsigned int width, unsigned int height, unsigned char* data);
        GLuint getId();
        glm::vec2 getSize();

        GLuint getFbId();
        void clear();
    };
}

#endif