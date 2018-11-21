#include "Player.h"

void Player::onInit(std::string meshLoc, std::string textureLoc)
{
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();
    // getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 10.0, -15.0f));
    // getEntity()->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

    std::shared_ptr<OluxEngine::Mesh> playerMesh = getCore()->getResources()->Load<OluxEngine::Mesh>(meshLoc);
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(playerMesh);

    std::shared_ptr<OluxEngine::Texture> tex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
	getEntity()->getComponent<OluxEngine::MeshRenderer>()->setTexture(tex);

    smc = getCore()->getEntity<OluxEngine::StaticModelCollider>()->getComponent<OluxEngine::StaticModelCollider>();

    speed = 15.0f;

    lastTime = SDL_GetTicks();
}

void Player::onBegin() 
{
	
}

void Player::update()
{
    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_R))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 10.0, -15.0f));
    }
    double now = SDL_GetTicks();
    double diffTime = now - lastTime;
    lastTime = now;
    deltaTime = diffTime / 1000.0f;

    glm::vec3 lp = getEntity()->getComponent<OluxEngine::Transform>()->getPosition() + glm::vec3(0, -1, 0);

    getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, -4, 0) * deltaTime);

	if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_W))
    {
        // getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, 0, speed) * deltaTime);

        float yRotation = getEntity()->getComponent<OluxEngine::Transform>()->getRotation().y;
        float xAmount = glm::sin(glm::radians(yRotation)) * speed;
        float zAmount = glm::cos(glm::radians(yRotation)) * speed;

        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(xAmount, 0, zAmount) * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_S))
    {
        float yRotation = getEntity()->getComponent<OluxEngine::Transform>()->getRotation().y;
        float xAmount = glm::sin(glm::radians(yRotation)) * speed;
        float zAmount = glm::cos(glm::radians(yRotation)) * speed;

        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(-xAmount, 0, -zAmount) * deltaTime);
    }
    
    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_A))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0, speed*5, 0) * deltaTime);

        getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0.0f, speed*5, 0.0f) * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_D))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0, -speed*5, 0) * deltaTime);

        getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0.0f, -speed*5, 0.0f) * deltaTime);
    }

    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_SPACE))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, 25, 0) * deltaTime);
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

    glm::vec3 pPos = getEntity()->getComponent<OluxEngine::Transform>()->getPosition();

    getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(np.x, np.y += 3.5f, np.z));
}