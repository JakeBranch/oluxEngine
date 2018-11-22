#ifndef OLUXENGINE_POSTPROCESSOR_H
#define OLUXENGINE_POSTPROCESSOR_H

#include "ShaderProgram.h"
#include "RenderTexture.h"

#include <memory>

namespace OluxEngine
{   
    class Core;

    class PostProcessor
    {
        public:
        PostProcessor(std::weak_ptr<Core> coreRef);
        std::shared_ptr<ShaderProgram> lightKeyShader;
        std::shared_ptr<ShaderProgram> nullShader;
        std::shared_ptr<ShaderProgram> blurShader;
        std::shared_ptr<ShaderProgram> mergeShader;

        std::shared_ptr<RenderTexture> sceneRt;
        std::shared_ptr<RenderTexture> lightkeyRt;
        std::shared_ptr<RenderTexture> blurRt;
        std::shared_ptr<RenderTexture> blur2Rt;
        std::shared_ptr<RenderTexture> blur3Rt;
        std::shared_ptr<RenderTexture> mergeRt;

        std::weak_ptr<Core> core;

        void display();
    };
}

#endif