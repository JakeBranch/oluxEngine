#include "EndScene.h"
#include "GameScene.h"

void EndScene::onInit()
{
    
}

void EndScene::onGui()
{
    std::shared_ptr<OluxEngine::Texture> background = getCore()->getResources()->Load<OluxEngine::Texture>("resources/endBackground.png");
    getCore()->getGui()->image(0, 0, 600, 800, background);

    std::shared_ptr<OluxEngine::Texture> tex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/button2.png");
    if(getCore()->getGui()->button(150, 350, 300, 100, tex))
    {
        getCore()->clearWorld();
        getCore()->addEntity()->addComponent<GameScene>();
    }
}