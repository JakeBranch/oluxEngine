#include "Player.h"

void Player::onInit(std::string meshLoc)
{
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();
    getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 0.0f, -15.0f));

    std::shared_ptr<OluxEngine::Mesh> playerMesh = getCore()->getResources()->Load<OluxEngine::Mesh>(meshLoc);
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(playerMesh);

    smc = getCore()->getEntity<OluxEngine::StaticModelCollider>()->getComponent<OluxEngine::StaticModelCollider>();

    speed = 4.0f;

    lastTime = SDL_GetTicks();
}

void Player::onBegin() 
{
	// std::cout << "onBegin" << std::endl;
}

void Player::update()
{
    double now = SDL_GetTicks();
    double diffTime = now - lastTime;
    lastTime = now;
    deltaTime = diffTime / 1000.0f;

    glm::vec3 lp = getEntity()->getComponent<OluxEngine::Transform>()->getPosition() + glm::vec3(0, -1, 0);

	if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_W))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, speed, 0) * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_S))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, -speed, 0) * deltaTime);
    }
    
    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_A))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(speed, 0, 0) * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_D))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(-speed, 0, 0) * deltaTime);
    }
    

    glm::vec3 np = getEntity()->getComponent<OluxEngine::Transform>()->getPosition() + glm::vec3(0, -1, 0);

    bool solved = false;
    glm::vec3 sp = smc->getCollisionResponse(np, lp, glm::vec3(1, 2, 1), solved);

    if(solved)
    {
        np = sp;
    }
    else
    {
        np = lp;
    }

    np += glm::vec3(0, 1, 0);
    
    getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(np);
}