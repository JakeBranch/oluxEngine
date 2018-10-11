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

		std::shared_ptr<VertexBuffer> texCoords = std::make_shared<VertexBuffer>();
		texCoords->add(glm::vec2(0.5f, 0.0f));
		texCoords->add(glm::vec2(0.0f, 1.0f));
		texCoords->add(glm::vec2(1.0f, 1.0f));

		shape = std::make_shared<VertexArray>();
		shape->setBuffer("in_Position", positions);
		shape->setBuffer("in_Color", colors);
		shape->setBuffer("in_TexCoord", texCoords);

		const char* vertLoc = "resources/shaders/simple.vert";
		const char* fragLoc = "resources/shaders/simple.frag";

		resources = std::make_shared<Resources>();
		shader = resources->Load<ShaderProgram>(vertLoc, fragLoc);
	}

	void MeshRenderer::onDisplay()
	{
		//shader->setUniform("in_Model", glm::mat4(1.0f));
		//shader->setUniform("in_Projection", glm::mat4(1.0f));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getId());

		shader->Draw(*shape);
	}

	void MeshRenderer::setTexture(std::shared_ptr<Texture> t)
	{
		texture = t;
	}
}
