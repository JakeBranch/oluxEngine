#include "Player.h"
#include "EndScene.h"

void Player::onInit(std::string meshLoc, std::string textureLoc)
{
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();
    getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(13.5f, -5.5f, 0.5f));

    std::shared_ptr<OluxEngine::Mesh> playerMesh = getCore()->getResources()->Load<OluxEngine::Mesh>(meshLoc);
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(playerMesh);

    std::shared_ptr<OluxEngine::Texture> tex = getCore()->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
	getEntity()->getComponent<OluxEngine::MeshRenderer>()->setTexture(tex);

    smc = getCore()->getEntity<OluxEngine::StaticModelCollider>()->getComponent<OluxEngine::StaticModelCollider>();

    getEntity()->addComponent<OluxEngine::BoxCollider>();

    speed = 15.0f;

    lastTime = SDL_GetTicks();

    std::shared_ptr<OluxEngine::MeshRenderer> mr = getEntity()->getComponent<OluxEngine::MeshRenderer>();
    std::shared_ptr<OluxEngine::Mesh> mesh = mr->getMesh();

    std::vector<OluxEngine::Face> meshFaces = mesh->getFaces();
    size = mesh->getSize();

    points = 0;
}

void Player::onUpdate()
{
    double now = SDL_GetTicks();
    double diffTime = now - lastTime;
    lastTime = now;
    deltaTime = diffTime / 1000.0f;

    glm::vec3 lp = getEntity()->getComponent<OluxEngine::Transform>()->getPosition() + glm::vec3(0, -1, 0);

    getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, -4, 0) * deltaTime);

    glm::vec3 direction;
    float yRotation = getEntity()->getComponent<OluxEngine::Transform>()->getRotation().y;
    direction.x = glm::sin(glm::radians(yRotation));
    direction.y = 0;
    direction.z = glm::cos(glm::radians(yRotation));

	if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_W))
    {
      
        direction.x *= speed;
        direction.z *= speed;
        direction.y = 0;

        getEntity()->getComponent<OluxEngine::Transform>()->translate(direction * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_S))
    {
        direction.x *= speed;
        direction.z *= speed;
        direction.y = 0;

        getEntity()->getComponent<OluxEngine::Transform>()->translate(-direction * deltaTime);
    }
    
    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_A))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0, speed*10, 0) * deltaTime);

        getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0.0f, speed*10, 0.0f) * deltaTime);
    }
    else if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_D))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0, -speed*10, 0) * deltaTime);

        getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->rotate(glm::vec3(0.0f, -speed*10, 0.0f) * deltaTime);
    }

    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_SPACE))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->translate(glm::vec3(0, 25, 0) * deltaTime);
    }

    glm::vec3 np = getEntity()->getComponent<OluxEngine::Transform>()->getPosition() + glm::vec3(0, -1, 0);

    bool solved = false;
    glm::vec3 sp = smc->getCollisionResponse(np, lp, glm::vec3(2, 4, 2), solved);

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

    getCore()->getEntity<OluxEngine::Camera>()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(np.x, np.y += 1.0f, np.z));
    
    std::list<std::shared_ptr<OluxEngine::Entity>> collectables;
    getCore()->getEntities(collectables, "Collectable");

    for(std::list<std::shared_ptr<OluxEngine::Entity>>::iterator it = collectables.begin();
		it != collectables.end(); it++)	
    {
        glm::vec3 collectableSize = (*it)->getComponent<OluxEngine::MeshRenderer>()->getMesh()->getSize();
        glm::vec3 collectablePos = (*it)->getComponent<OluxEngine::Transform>()->getPosition();

         glm::vec3 playerPos = getEntity()->getComponent<OluxEngine::Transform>()->getPosition();

        if(getEntity()->getComponent<OluxEngine::BoxCollider>()->isColliding(np, collectablePos, collectableSize))
        {
            (*it)->destroy();

            points++;
            if(points >= collectables.size())
            {
                getCore()->clearWorld();
                getCore()->addEntity()->addComponent<EndScene>();
            }
        }
    }

    std::shared_ptr<OluxEngine::SpotLight> spotLight = getCore()->getEntity<OluxEngine::SpotLight>()->getComponent<OluxEngine::SpotLight>();
    spotLight->setPosition(np);
    spotLight->setDirection(direction);


    //-----------------------------------------------------------------------------------------------------------Cheats
    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_R))
    {
        getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(13.5f, -5.5f, 0.5f));
    }

    if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_F))
    {
        getCore()->clearWorld();
        getCore()->addEntity()->addComponent<EndScene>();
    }
}