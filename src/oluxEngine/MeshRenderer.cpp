#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "Core.h"

#include <iostream>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

namespace OluxEngine
{

	void MeshRenderer::onInit()
	{
		angle = 0;
		/*std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
		positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
		positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		positions->add(glm::vec3(0.5f, -0.5f, 0.0f)); 

		/*std::shared_ptr<VertexBuffer> colors = std::make_shared<VertexBuffer>();
		colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));*/

		/*std::shared_ptr<VertexBuffer> texCoords = std::make_shared<VertexBuffer>();
		texCoords->add(glm::vec2(0.5f, 0.0f));
		texCoords->add(glm::vec2(0.0f, 1.0f));
		texCoords->add(glm::vec2(1.0f, 1.0f));*/

		shape = std::make_shared<VertexArray>("resources/curuthers.obj");
		
		/*shape->setBuffer("in_Position", positions);
		shape->setBuffer("in_Color", colors);
		shape->setBuffer("in_TexCoord", texCoords);*/

		const char* vertLoc = "resources/shaders/simple.vert";
		const char* fragLoc = "resources/shaders/simple.frag";

		// resources = std::make_shared<Resources>();
		// shader = resources->Load;
		shader = getCore()->getResources()->Load<ShaderProgram>(vertLoc, fragLoc);
		// getCore()->getResources();

	}

	void MeshRenderer::onDisplay()
	{
		glm::mat4 model(1.0f);
		glm::mat4 viewMatrix = getCore()->getCamera()->getViewMatrix();

		shader->SetUniform("in_View", viewMatrix);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
    	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
		shader->SetUniform("in_Model", model);

		shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		shader->SetUniform("in_Texture", texture);

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getId());*/

		shader->Draw(*shape);

		angle += 0.1f;
	}

	void MeshRenderer::setTexture(std::shared_ptr<Texture> t)
	{
		texture = t;
	}
}
