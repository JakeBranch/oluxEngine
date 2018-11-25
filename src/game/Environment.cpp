#include "Environment.h"

void Environment::onInit(std::string meshLoc)
{
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();

    std::shared_ptr<OluxEngine::Mesh> envMesh = getCore()->getResources()->Load<OluxEngine::Mesh>(meshLoc);
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(envMesh);

    getEntity()->addComponent<OluxEngine::StaticModelCollider>();
}

void Environment::onBegin()
{

}

void Environment::onUpdate()
{

}