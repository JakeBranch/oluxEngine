#include <oluxEngine/OluxEngine.h>
#include <glm/glm.hpp>

#include <cstdio>
#include <iostream>
#include <memory>

#include <exception>

#include <GL\glew.h>

#include <SDL.h>

#include <SDL_opengl.h>

#include "TestScene.h"
#include "Environment.h"
#include "Player.h"

int main(int argc, char* argv[])
{
	try
	{
		std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

		//------------------------------------------Test scene
		std::shared_ptr<OluxEngine::Entity> testScene = core->addEntity();
		testScene->addComponent<TestScene>();

		//------------------------------------------Sound effect
		/*std::shared_ptr<OluxEngine::Sound> soundfx = core->getResources()->Load<OluxEngine::Sound>("dixie_horn.ogg");
		soundfx->play();*/

		//------------------------------------------Main camera
		std::shared_ptr<OluxEngine::Entity> mainCam = core->addEntity();
		mainCam->addComponent<OluxEngine::Camera>();
		// mainCam->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 10.0f, 0.0f));
		mainCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));


		std::shared_ptr<OluxEngine::Entity> secondCam = core->addEntity();
		secondCam->addComponent<OluxEngine::Camera>();
		secondCam->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-10.0f, 3.0f, -0.0f));
		secondCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		//-------------------------------------------Directional light
		std::shared_ptr<OluxEngine::Entity> lights = core->addEntity();
		lights->addComponent<OluxEngine::DirectionalLight>();
		lights->addComponent<OluxEngine::SpotLight>();
		
		std::shared_ptr<OluxEngine::Entity> pLight1 = core->addEntity();
		pLight1->addComponent<OluxEngine::PointLight>();
		pLight1->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight1->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(5.0f, 0.0f, -5.0f));

		std::shared_ptr<OluxEngine::Entity> pLight2 = core->addEntity();
		pLight2->addComponent<OluxEngine::PointLight>();
		pLight2->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight2->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-5.0f, 0.0f, -5.0f));

		//-------------------------------------------Environment
		std::shared_ptr<OluxEngine::Entity> environment = core->addEntity();
		environment->addComponent<Environment>("resources/re_hall_baked.obj");

		std::shared_ptr<OluxEngine::Texture> envTexture = core->getResources()->Load<OluxEngine::Texture>("resources/re_hall_diffuse.png");
		environment->getComponent<OluxEngine::MeshRenderer>()->setTexture(envTexture);

		//-------------------------------------------Player model
		// std::shared_ptr<OluxEngine::Entity> player = core->addEntity();
		// player->addComponent<OluxEngine::MeshRenderer>();

		// player->addComponent<OluxEngine::Transform>();
		// player->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 0.0f, -15.0f));

		// std::shared_ptr<OluxEngine::Texture> t = core->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
		// player->getComponent<OluxEngine::MeshRenderer>()->setTexture(t);

		// std::shared_ptr<OluxEngine::Mesh> playerMesh = core->getResources()->Load<OluxEngine::Mesh>("resources/curuthers.obj");
		// player->getComponent<OluxEngine::MeshRenderer>()->setMesh(playerMesh);

		std::shared_ptr<OluxEngine::Entity> player = core->addEntity();
		player->addComponent<Player>("resources/curuthers.obj", "resources/curuthers_diffuse.png");

		// std::shared_ptr<OluxEngine::Texture> playerTex = core->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
		// player->getComponent<OluxEngine::MeshRenderer>()->setTexture(playerTex);

		//--------------------------------------------Start Game
		core->Start(); 
	}
	catch(OluxEngine::Exception& e)
	{

		std::cout << "OluxEngine Exception: " << e.what() << std::endl;
	}

}