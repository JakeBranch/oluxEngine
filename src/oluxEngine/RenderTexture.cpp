#include "RenderTexture.h"
#include <iostream>

namespace OluxEngine
{
	std::shared_ptr<RenderTexture> RenderTexture::Load(int width, int height)
	{
        std::shared_ptr<RenderTexture> rtn = std::make_shared<RenderTexture>();
        rtn->size.x = width;
        rtn->size.y = height;

        glGenTextures(1, &rtn->texId);
        glBindTexture(GL_TEXTURE_2D, rtn->texId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenFramebuffers(1, &rtn->fbo);
        if(!rtn->fbo)
        {
            throw Exception("Failed to generate render texture FBO");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, rtn->fbo);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rtn->texId, 0);
   
        GLuint rbo = 0;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return rtn;
    }

    GLuint RenderTexture::getFbId()
    {
        return fbo;
    }

    glm::vec2 RenderTexture::getSize()
    {
        return size;
    }

    GLuint RenderTexture::getId()
    {
        return texId;
    }

    void RenderTexture::clear()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}