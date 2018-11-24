#include "PostProcessor.h"
#include "Core.h"
namespace OluxEngine
{
    PostProcessor::PostProcessor(std::weak_ptr<Core> coreRef)
    {
        core = coreRef;
        std::shared_ptr<Core> tmp = core.lock();
        lightKeyShader = tmp->getResources()->Load<ShaderProgram>("resources/shaders/lightkeypass.vert", "resources/shaders/lightkeypass.frag");
        nullShader = tmp->getResources()->Load<ShaderProgram>("resources/shaders/nullpass.vert", "resources/shaders/nullpass.frag");
        blurShader = tmp->getResources()->Load<ShaderProgram>("resources/shaders/blur.vert", "resources/shaders/blur.frag");
        mergeShader = tmp->getResources()->Load<ShaderProgram>("resources/shaders/mergepass.vert", "resources/shaders/mergepass.frag");
    
        sceneRt = tmp->getResources()->Load<RenderTexture>(600, 800);
        lightkeyRt = tmp->getResources()->Load<RenderTexture>(600, 800);
        blurRt = tmp->getResources()->Load<RenderTexture>(600, 800);
        blur2Rt = tmp->getResources()->Load<RenderTexture>(600, 800);
        blur3Rt = tmp->getResources()->Load<RenderTexture>(600, 800);
        mergeRt = tmp->getResources()->Load<RenderTexture>(600, 800);
    }

    void PostProcessor::display()
    {
        lightKeyShader->SetUniform("in_Texture", sceneRt);
        lightKeyShader->Draw(lightkeyRt);

        blurShader->SetUniform("in_Texture", lightkeyRt);
        blurShader->Draw(blurRt);

        blurShader->SetUniform("in_Texture", blurRt);
        blurShader->Draw(blur2Rt);

        blurShader->SetUniform("in_Texture", blur2Rt);
        blurShader->Draw(blur3Rt);

        mergeShader->SetUniform("in_TextureA", sceneRt);
        mergeShader->SetUniform("in_TextureB", blur3Rt);
        mergeShader->Draw(mergeRt);

        nullShader->setViewport(glm::vec4(0, 0, 600, 800));
        nullShader->SetUniform("in_Texture", sceneRt);
        nullShader->Draw();
    }
}