#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"

#include <iostream>

namespace OluxEngine
{

void MeshRenderer::onInit()
{
    std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
    positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
    positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
    positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

    std::shared_ptr<VertexBuffer> colors = std::make_shared<VertexBuffer>();
    colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    shape = std::make_shared<VertexArray>();
    shape->setBuffer("in_Position", positions);
    shape->setBuffer("in_Color", colors);

    const char* vertLoc = "resources/shaders/simple.vert";
    const char* fragLoc = "resources/shaders/simple.frag";

    shader = std::make_shared<ShaderProgram>(vertLoc, fragLoc);
}

void MeshRenderer::onDisplay()
{
    //shader->setUniform("in_Model", glm::mat4(1.0f));
    //shader->setUniform("in_Projection", glm::mat4(1.0f));
    shader->Draw(*shape);
}

}
