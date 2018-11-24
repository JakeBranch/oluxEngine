#include "GameScene.h"
#include "Environment.h"
#include "Player.h"

void GameScene::onInit()
{
    // began = false;
    std::cout << "START" << std::endl;
    // std::shared_ptr<OluxEngine::Entity> mainCam = getCore()->addEntity();
    // mainCam->addComponent<OluxEngine::Camera>();
    // mainCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

    // std::shared_ptr<OluxEngine::Entity> dLight = getCore()->addEntity();
    // dLight->addComponent<OluxEngine::DirectionalLight>();

    // std::shared_ptr<OluxEngine::Entity> sLight = getCore()->addEntity();
    // sLight->addComponent<OluxEngine::SpotLight>();

    // std::shared_ptr<OluxEngine::Entity> pLight1= getCore()->addEntity();
    // pLight1->addComponent<OluxEngine::PointLight>();
    // pLight1->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    // pLight1->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(42.0f, 9.0f, 27.0f));

    // std::shared_ptr<OluxEngine::Entity> pLight2= getCore()->addEntity();
    // pLight2->addComponent<OluxEngine::PointLight>();
    // pLight2->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    // pLight2->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-12.0f, -5.0f, 29.0f));

    // std::shared_ptr<OluxEngine::Entity> pLight3= getCore()->addEntity();
    // pLight3->addComponent<OluxEngine::PointLight>();
    // pLight3->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    // pLight3->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(23.0f, -5.0f, 30.0f));
    
    // std::shared_ptr<OluxEngine::Entity> pLight4= getCore()->addEntity();
    // pLight4->addComponent<OluxEngine::PointLight>();
    // pLight4->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    // pLight4->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-30.0f, 4.0f, 51.0f));
    
    // std::shared_ptr<OluxEngine::Entity> pLight5= getCore()->addEntity();
    // pLight5->addComponent<OluxEngine::PointLight>();
    // pLight5->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    // pLight5->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-19.0f, 8.0f, 16.0f));

    // std::shared_ptr<OluxEngine::Entity> env = getCore()->addEntity();
    // env->addComponent<Environment>("resources/newMaze2.obj");
    // std::shared_ptr<OluxEngine::Texture> envTex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/re_hall_diffuse.png");
    // env->getComponent<OluxEngine::MeshRenderer>()->setTexture(envTex);

    // std::cout << "2ND FINAL" << std::endl;

    std::shared_ptr<OluxEngine::Entity> collectable = getCore()->addEntity();
    // collectable->addComponent<OluxEngine::MeshRenderer>();
    // collectable->addComponent<OluxEngine::Transform>();
    // collectable->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-19.5f, -7.5, 23.5f));
    // std::shared_ptr<OluxEngine::Mesh> mesh = getCore()->getResources()->Load<OluxEngine::Mesh>("resources/collectable.obj");
    // collectable->getComponent<OluxEngine::MeshRenderer>()->setMesh(mesh);
    // std::shared_ptr<OluxEngine::Texture> colTex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
    // collectable->getComponent<OluxEngine::MeshRenderer>()->setTexture(colTex);

    // std::shared_ptr<OluxEngine::Entity> player = getCore()->addEntity();
    // player->addComponent<Player>("resources/curuthers.obj", "resources/curuthers_diffuse.png");
    
    // std::cout << "FINAL" << std::endl;
}

void GameScene::onGui()
{
    if(getCore()->getGui()->button(300, 300, 300, 100))
    {
        std::cout << "INSIDE" << std::endl;
    }
}