#include "Environment.h"

void Environment::onInit(std::string meshLoc)
{
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();
    // getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 0.0f, -25.0f));
    // getEntity()->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

    std::shared_ptr<OluxEngine::Mesh> envMesh = getCore()->getResources()->Load<OluxEngine::Mesh>(meshLoc);
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(envMesh);

    getEntity()->addComponent<OluxEngine::StaticModelCollider>();
}

void Environment::onBegin()
{

}

void Environment::update()
{

}