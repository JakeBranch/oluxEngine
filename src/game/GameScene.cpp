#include "GameScene.h"
#include "Environment.h"
#include "Player.h"
#include "Collectable.h"

void GameScene::onInit()
{

    std::shared_ptr<OluxEngine::Entity> mainCam = getCore()->addEntity();
    mainCam->addComponent<OluxEngine::Camera>();
    mainCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

    std::shared_ptr<OluxEngine::Entity> dLight = getCore()->addEntity();
    dLight->addComponent<OluxEngine::DirectionalLight>();
    dLight->getComponent<OluxEngine::DirectionalLight>()->setColor(glm::vec3(0.02f, 0.02f, 0.02f));

    std::shared_ptr<OluxEngine::Entity> sLight = getCore()->addEntity();
    sLight->addComponent<OluxEngine::SpotLight>();
    sLight->getComponent<OluxEngine::SpotLight>()->setColor(glm::vec3(0.7f, 0.7f, 0.7f));

    std::shared_ptr<OluxEngine::Entity> pLight1= getCore()->addEntity();
    pLight1->addComponent<OluxEngine::PointLight>();
    pLight1->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 0.3f, 0.0f));
    pLight1->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(42.0f, 9.0f, 27.0f));
    pLight1->getComponent<OluxEngine::PointLight>()->setAmbientIntensity(0.01f);

    std::shared_ptr<OluxEngine::Entity> pLight2= getCore()->addEntity();
    pLight2->addComponent<OluxEngine::PointLight>();
    pLight2->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 0.3f, 0.0f));
    pLight2->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-12.0f, -5.0f, 29.0f));
    pLight2->getComponent<OluxEngine::PointLight>()->setAmbientIntensity(0.01f);

    std::shared_ptr<OluxEngine::Entity> pLight3= getCore()->addEntity();
    pLight3->addComponent<OluxEngine::PointLight>();
    pLight3->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 0.3f, 0.0f));
    pLight3->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(23.0f, -5.0f, 30.0f));
    pLight3->getComponent<OluxEngine::PointLight>()->setAmbientIntensity(0.01f);
    
    std::shared_ptr<OluxEngine::Entity> pLight4= getCore()->addEntity();
    pLight4->addComponent<OluxEngine::PointLight>();
    pLight4->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 0.3f, 0.0f));
    pLight4->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-30.0f, 4.0f, 51.0f));
    pLight4->getComponent<OluxEngine::PointLight>()->setAmbientIntensity(0.01f);
    
    std::shared_ptr<OluxEngine::Entity> pLight5= getCore()->addEntity();
    pLight5->addComponent<OluxEngine::PointLight>();
    pLight5->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 0.3f, 0.0f));
    pLight5->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-19.0f, 8.0f, 16.0f));
    pLight5->getComponent<OluxEngine::PointLight>()->setAmbientIntensity(0.01f);

    std::shared_ptr<OluxEngine::Entity> env = getCore()->addEntity();
    env->addComponent<Environment>("resources/environment.obj");
    std::shared_ptr<OluxEngine::Texture> envTex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/environment.png");
    env->getComponent<OluxEngine::MeshRenderer>()->setTexture(envTex);

    std::shared_ptr<OluxEngine::Entity> collectable1 = getCore()->addEntity();
    collectable1->addComponent<Collectable>();
    collectable1->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(5.0f, -7.5f, 65.0f));

    std::shared_ptr<OluxEngine::Entity> collectable2 = getCore()->addEntity();
    collectable2->addComponent<Collectable>();
    collectable2->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(37.0f, 12.5f, -38.0f));

    std::shared_ptr<OluxEngine::Entity> collectable3 = getCore()->addEntity();
    collectable3->addComponent<Collectable>();
    collectable3->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-10.0f, 2.0f, -72.5f));

    std::shared_ptr<OluxEngine::Entity> collectable4 = getCore()->addEntity();
    collectable4->addComponent<Collectable>();
    collectable4->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-9.5f, 12.0f, -80.5f));

    std::shared_ptr<OluxEngine::Entity> player = getCore()->addEntity();
    player->addComponent<Player>("resources/curuthers.obj", "resources/curuthers_diffuse.png");
}

void GameScene::onGui()
{
    
}