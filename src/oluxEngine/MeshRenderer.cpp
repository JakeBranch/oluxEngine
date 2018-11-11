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
		material = std::make_shared<Material>();
		dirLight = std::make_shared<DirectionalLight>();
		pointLight = std::make_shared<PointLight>();
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
		model = glm::translate(model, glm::vec3(0, 0.0f, -15.0f));
    	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		shader->SetUniform("in_Model", model);

		shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		//shader->SetUniform("lightPos", phongLight->getPosition());
		shader->SetUniform("cameraPos", getCore()->getCamera()->getPosition());
		//shader->SetUniform("lightColor", phongLight->getColor());

		shader->SetUniform("material.specular", material->getSpecular());
		shader->SetUniform("material.shininess", material->getShininess());
		shader->SetUniform("material.diffuse", texture);

		shader->SetUniform("dirLight.direction", dirLight->getDirection());
		shader->SetUniform("dirLight.ambient", dirLight->getAmbient());
		shader->SetUniform("dirLight.diffuse", dirLight->getDiffuse());
		shader->SetUniform("dirLight.specular", dirLight->getSpecular());

		shader->SetUniform("pointLight.position", pointLight->getPosition());
		shader->SetUniform("pointLight.constant", pointLight->getConstant());
		shader->SetUniform("pointLight.linear", pointLight->getLinear());
		shader->SetUniform("pointLight.quadratic", pointLight->getQuadratic());
		shader->SetUniform("pointLight.ambient", pointLight->getAmbient());
		shader->SetUniform("pointLight.diffuse", pointLight->getDiffuse());
		shader->SetUniform("pointLight.specular", pointLight->getSpecular());

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

	std::shared_ptr<Material> MeshRenderer::getMaterial()
	{
		return material;
	}
}
