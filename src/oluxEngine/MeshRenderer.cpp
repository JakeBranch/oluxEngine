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
		material = std::make_shared<Material>();
		
		std::string vertShader = "resources/shaders/simple.vert";
		std::string fragShader = "resources/shaders/simple.frag";

		material->setShader(getCore()->getResources()->Load<ShaderProgram>(vertShader, fragShader));

		angle = 0;
	}

	/**
	* Displays the mesh.
	*
	* Sets uniform shaders and draws mesh
	*/
	void MeshRenderer::onDisplay()
	{
		material->getShader()->SetUniform("in_View", getCore()->getCamera()->getViewMatrix());

		material->getShader()->SetUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());

		material->getShader()->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f),
     				(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		material->getShader()->SetUniform("cameraPos", getCore()->getCamera()->getPosition());

		//----------------------------------------------------------------------Set material properties
		material->getShader()->SetUniform("material.specular", material->getSpecular());
		material->getShader()->SetUniform("material.shininess", material->getShininess());
		material->getShader()->SetUniform("material.diffuse", material->getDiffuse());

		//-----------------------------------------------------------------------|APPLY DIRECTIONAL LIGHT|
		material->getShader()->SetUniform("dirLight.direction", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getDirection());
		material->getShader()->SetUniform("dirLight.ambient", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getAmbient());
		material->getShader()->SetUniform("dirLight.diffuse", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getDiffuse());
		material->getShader()->SetUniform("dirLight.specular", getCore()->getEntity<DirectionalLight>()->getComponent<DirectionalLight>()->getSpecular());

		//-----------------------------------------------------------------------|APPLY POINT LIGHTS|
		std::vector<std::shared_ptr<Entity>> pointLights;
		getCore()->getEntities<PointLight>(pointLights);

		material->getShader()->SetUniform("numOfPointLights", (int)pointLights.size());

		for(size_t i = 0; i < pointLights.size(); i++)
		{
			std::shared_ptr<PointLight> light = pointLights.at(i)->getComponent<PointLight>();

			std::string prefix = "pointLights[";
			prefix += std::to_string(i);
			prefix += "].";

			std::string uniformLoc;	
		
			uniformLoc = prefix + "position";
			material->getShader()->SetUniform(uniformLoc, light->getPosition());

			uniformLoc = prefix + "constant";
			material->getShader()->SetUniform(uniformLoc, light->getConstant());

			uniformLoc = prefix + "linear";
			material->getShader()->SetUniform(uniformLoc, light->getLinear());

			uniformLoc = prefix + "quadratic";
			material->getShader()->SetUniform(uniformLoc, light->getQuadratic());

			uniformLoc = prefix + "ambient";
			material->getShader()->SetUniform(uniformLoc, light->getAmbient());

			uniformLoc = prefix + "diffuse";
			material->getShader()->SetUniform(uniformLoc, light->getDiffuse());

			uniformLoc = prefix + "specular";
			material->getShader()->SetUniform(uniformLoc, light->getSpecular());
		}

		//-----------------------------------------------------------------------|APPLY SPOT LIGHTS|
		std::vector<std::shared_ptr<Entity>> spotLights;
		getCore()->getEntities<SpotLight>(spotLights);

		material->getShader()->SetUniform("numOfSpotLights", (int)spotLights.size());

		for(size_t i = 0; i < spotLights.size(); i++)
		{
			std::shared_ptr<SpotLight> light = spotLights.at(i)->getComponent<SpotLight>();

			std::string prefix = "spotLights[";
			prefix += std::to_string(i);
			prefix += "].";

			std::string uniformLoc;

			uniformLoc = prefix + "position";
			material->getShader()->SetUniform(uniformLoc, light->getPosition());

			uniformLoc = prefix + "direction";
			material->getShader()->SetUniform(uniformLoc, light->getDirection());

			uniformLoc = prefix + "cutOff";
			material->getShader()->SetUniform(uniformLoc, light->getCutoff());

			uniformLoc = prefix + "outerCutOff";
			material->getShader()->SetUniform(uniformLoc, light->getOuterCutoff());

			uniformLoc = prefix + "constant";
			material->getShader()->SetUniform(uniformLoc, light->getConstant());

			uniformLoc = prefix + "linear";
			material->getShader()->SetUniform(uniformLoc, light->getLinear());

			uniformLoc = prefix + "quadratic";
			material->getShader()->SetUniform(uniformLoc, light->getQuadratic());

			uniformLoc = prefix + "ambient";
			material->getShader()->SetUniform(uniformLoc, light->getAmbient());

			uniformLoc = prefix + "diffuse";
			material->getShader()->SetUniform(uniformLoc, light->getDiffuse());

			uniformLoc = prefix + "specular";
			material->getShader()->SetUniform(uniformLoc, light->getSpecular());
		}

		material->getShader()->Draw(*mesh->getShape());
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

	std::shared_ptr<Mesh> MeshRenderer::getMesh()
	{
		return mesh;
	}
}
