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

	/**
	* Creates vertex array of mesh
	*/
	void MeshRenderer::onInit(std::string meshLoc)
	{
		angle = 0;
		shape = std::make_shared<VertexArray>(meshLoc);
	}

	/**
	* Displays the mesh.
	*
	* Sets uniform shaders and draws mesh
	*/
	void MeshRenderer::onDisplay()
	{
		glm::mat4 model(1.0f);
		glm::mat4 viewMatrix = getCore()->getCamera()->getViewMatrix();

		shader->SetUniform("in_View", viewMatrix);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
    	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
		shader->SetUniform("in_Model", model);

		shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		shader->SetUniform("in_Texture", texture);

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getId());*/

		shader->Draw(*shape);

		angle += 0.1f;
	}

	/**
	* Set texture attached to the mesh
	*/
	void MeshRenderer::setTexture(std::shared_ptr<Texture> t)
	{
		texture = t;
	}

	/**
	* Set shaders attached to the mesh
	*/
	void MeshRenderer::setShaders(std::string vertShader, std::string fragShader)
	{
		const char* vertLoc = vertShader.c_str();
		const char* fragLoc = fragShader.c_str();

		shader = getCore()->getResources()->Load<ShaderProgram>(vertLoc, fragLoc);
	}
}
