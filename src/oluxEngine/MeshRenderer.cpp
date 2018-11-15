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
	void MeshRenderer::onInit()
	{
		angle = 0;

		material = std::make_shared<Material>();
		
		std::string vertShader = "resources/shaders/simple.vert";
		std::string fragShader = "resources/shaders/simple.frag";
		const char* vertLoc = vertShader.c_str();
		const char* fragLoc = fragShader.c_str();

		material->setShader(getCore()->getResources()->Load<ShaderProgram>(vertLoc, fragLoc));
	}

	/**
	* Displays the mesh.
	*
	* Sets uniform shaders and draws mesh
	*/
	void MeshRenderer::onDisplay()
	{
		glm::mat4 viewMatrix = getCore()->getCamera()->getViewMatrix();

		material->getShader()->SetUniform("in_View", viewMatrix);

		material->getShader()->SetUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());

		material->getShader()->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		material->getShader()->SetUniform("cameraPos", getCore()->getCamera()->getPosition());

		//----------------------------------------------------------------------Set material properties
		material->getShader()->SetUniform("material.specular", material->getSpecular());
		material->getShader()->SetUniform("material.shininess", material->getShininess());
		material->getShader()->SetUniform("material.diffuse", material->getDiffuse());

		//-----------------------------------------------------------------------Set directional light properties
		material->getShader()->SetUniform("dirLight.direction", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getDirection());
		material->getShader()->SetUniform("dirLight.ambient", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getAmbient());
		material->getShader()->SetUniform("dirLight.diffuse", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getDiffuse());
		material->getShader()->SetUniform("dirLight.specular", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getSpecular());

		//----------------------------------------------------------------------Set point light properties
		material->getShader()->SetUniform("pointLight.position", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getPosition());
		material->getShader()->SetUniform("pointLight.constant", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getConstant());
		material->getShader()->SetUniform("pointLight.linear", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getLinear());
		material->getShader()->SetUniform("pointLight.quadratic", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getQuadratic());
		material->getShader()->SetUniform("pointLight.ambient", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getAmbient());
		material->getShader()->SetUniform("pointLight.diffuse", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getDiffuse());
		material->getShader()->SetUniform("pointLight.specular", getCore()->getEntity<PointLight>()->getComponent<PointLight>()->getSpecular());

		//-------------------------------------------------------------------------Set spot light properties
		// material->getShader()->SetUniform("spotLight.position", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getPosition());
		// material->getShader()->SetUniform("spotLight.direction", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getDirection());
		// material->getShader()->SetUniform("spotLight.cutOff", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getCutoff());
		// material->getShader()->SetUniform("spotLight.outerCutOff", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getOuterCutoff());
		// material->getShader()->SetUniform("spotLight.constant", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getConstant());
		// material->getShader()->SetUniform("spotLight.linear", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getLinear());
		// material->getShader()->SetUniform("spotLight.quadratic", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getQuadratic());
		// material->getShader()->SetUniform("spotLight.ambient", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getAmbient());
		// material->getShader()->SetUniform("spotLight.diffuse", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getDiffuse());
		// material->getShader()->SetUniform("spotLight.specular", getCore()->getEntity<SpotLight>()->getComponent<SpotLight>()->getSpecular());

		material->getShader()->Draw(*mesh->getShape());

		angle += 0.1f;
	}

	/**
	* Set texture attached to the mesh
	*/
	void MeshRenderer::setTexture(std::shared_ptr<Texture> t)
	{
		material->setDiffuse(t);
	}

	void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
	{
		this->mesh = mesh;
	}

	/**
	* Set shaders attached to the mesh
	*/
	void MeshRenderer::setShaders(std::string vertShader, std::string fragShader)
	{
	
	}

	std::shared_ptr<Material> MeshRenderer::getMaterial()
	{
		return material;
	}
}
