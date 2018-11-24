#include "MainMenu.h"
#include "GameScene.h"

void MainMenu::onInit()
{
    std::cout << "onInit" << std::endl;
}

void MainMenu::onGui()
{
    if(getCore()->getGui()->button(0, 0, 300, 100))
    {
        play();
    }
}

void MainMenu::play()
{
    getCore()->addEntity()->addComponent<GameScene>();
    getEntity()->destroy();
    getCore()->getEntity<OluxEngine::PointLight>()->destroy();
}