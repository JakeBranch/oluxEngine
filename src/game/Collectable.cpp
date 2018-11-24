#include "Collectable.h"

void Collectable::onInit()
{
    getEntity()->setTag("Collectable");
    getEntity()->addComponent<OluxEngine::MeshRenderer>();
    getEntity()->addComponent<OluxEngine::Transform>();
    getEntity()->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-5.5f, -7.5f, 24.5f));
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setMesh(getCore()->getResources()->Load<OluxEngine::Mesh>("resources/collectable.obj"));
    getEntity()->getComponent<OluxEngine::MeshRenderer>()->setTexture(getCore()->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png"));
}