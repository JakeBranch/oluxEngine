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
		spotLight = std::make_shared<SpotLight>();

		pointLight->setColor(glm::vec3(0.4f, 0.7f, 0.1f));
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

		material->getShader()->SetUniform("in_View", viewMatrix);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0.0f, -15.0f));
    	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		material->getShader()->SetUniform("in_Model", model);

		material->getShader()->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		material->getShader()->SetUniform("cameraPos", getCore()->getCamera()->getPosition());

		//----------------------------------------------------------------------Set material properties
		material->getShader()->SetUniform("material.specular", material->getSpecular());
		material->getShader()->SetUniform("material.shininess", material->getShininess());
		material->getShader()->SetUniform("material.diffuse", material->getDiffuse());

		//-----------------------------------------------------------------------Set directional light properties
		material->getShader()->SetUniform("dirLight.direction", dirLight->getDirection());
		material->getShader()->SetUniform("dirLight.ambient", dirLight->getAmbient());
		material->getShader()->SetUniform("dirLight.diffuse", dirLight->getDiffuse());
		material->getShader()->SetUniform("dirLight.specular", dirLight->getSpecular());

		//----------------------------------------------------------------------Set point light properties
		material->getShader()->SetUniform("pointLight.position", pointLight->getPosition());
		material->getShader()->SetUniform("pointLight.constant", pointLight->getConstant());
		material->getShader()->SetUniform("pointLight.linear", pointLight->getLinear());
		material->getShader()->SetUniform("pointLight.quadratic", pointLight->getQuadratic());
		material->getShader()->SetUniform("pointLight.ambient", pointLight->getAmbient());
		material->getShader()->SetUniform("pointLight.diffuse", pointLight->getDiffuse());
		material->getShader()->SetUniform("pointLight.specular", pointLight->getSpecular());

		//-------------------------------------------------------------------------Set spot light properties
		// material->getShader()->SetUniform("spotLight.position", spotLight->getPosition());
		// material->getShader()->SetUniform("spotLight.direction", spotLight->getDirection());
		// material->getShader()->SetUniform("spotLight.cutOff", spotLight->getCutoff());
		// material->getShader()->SetUniform("spotLight.outerCutOff", spotLight->getOuterCutoff());
		// material->getShader()->SetUniform("spotLight.constant", spotLight->getConstant());
		// material->getShader()->SetUniform("spotLight.linear", spotLight->getLinear());
		// material->getShader()->SetUniform("spotLight.quadratic", spotLight->getQuadratic());
		// material->getShader()->SetUniform("spotLight.ambient", spotLight->getAmbient());
		// material->getShader()->SetUniform("spotLight.diffuse", spotLight->getDiffuse());
		// material->getShader()->SetUniform("spotLight.specular", spotLight->getSpecular());

		material->getShader()->Draw(*shape);

		angle += 0.1f;
	}

	/**
	* Set texture attached to the mesh
	*/
	void MeshRenderer::setTexture(std::shared_ptr<Texture> t)
	{
		material->setDiffuse(t);
	}

	/**
	* Set shaders attached to the mesh
	*/
	void MeshRenderer::setShaders(std::string vertShader, std::string fragShader)
	{
		const char* vertLoc = vertShader.c_str();
		const char* fragLoc = fragShader.c_str();

		material->setShader(getCore()->getResources()->Load<ShaderProgram>(vertLoc, fragLoc));
	}

	std::shared_ptr<Material> MeshRenderer::getMaterial()
	{
		return material;
	}
}
