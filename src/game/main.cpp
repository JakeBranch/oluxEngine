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
#include "MainMenu.h"
#include "Environment.h"
#include "Player.h"

int main(int argc, char* argv[])
{
	try
	{
		std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

		//------------------------------------------Test scene
		std::shared_ptr<OluxEngine::Entity> mainMenu = core->addEntity();
		mainMenu->addComponent<MainMenu>();

		// // //------------------------------------------Sound effect
		// /*std::shared_ptr<OluxEngine::Sound> soundfx = core->getResources()->Load<OluxEngine::Sound>("dixie_horn.ogg");
		// soundfx->play();*/

		// ------------------------------------------Main camera
		// std::shared_ptr<OluxEngine::Entity> mainCam = core->addEntity();
		// mainCam->addComponent<OluxEngine::Camera>();
		// // mainCam->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(0.0f, 10.0f, 0.0f));
		// mainCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));


		// std::shared_ptr<OluxEngine::Entity> secondCam = core->addEntity();
		// secondCam->addComponent<OluxEngine::Camera>();
		// secondCam->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-10.0f, 3.0f, -0.0f));
		// secondCam->getComponent<OluxEngine::Transform>()->setLocalRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		//------------------------------------------lights
		std::shared_ptr<OluxEngine::Entity> lights = core->addEntity();
		lights->addComponent<OluxEngine::DirectionalLight>();
		lights->addComponent<OluxEngine::SpotLight>();
		
		std::shared_ptr<OluxEngine::Entity> pLight1 = core->addEntity();
		pLight1->addComponent<OluxEngine::PointLight>();
		pLight1->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight1->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(42.0f, 9.0f, 27.0f));

		std::shared_ptr<OluxEngine::Entity> pLight3 = core->addEntity();
		pLight3->addComponent<OluxEngine::PointLight>();
		pLight3->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight3->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-12.0f, -5.0f, 29.0f));

		std::shared_ptr<OluxEngine::Entity> pLight4 = core->addEntity();
		pLight4->addComponent<OluxEngine::PointLight>();
		pLight4->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight4->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(23.0f, -5.0f, 30.0f));

		std::shared_ptr<OluxEngine::Entity> pLight5 = core->addEntity();
		pLight5->addComponent<OluxEngine::PointLight>();
		pLight5->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight5->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-30.0f, 4.0f, 51.0f));

		std::shared_ptr<OluxEngine::Entity> pLight6 = core->addEntity();
		pLight6->addComponent<OluxEngine::PointLight>();
		pLight6->getComponent<OluxEngine::PointLight>()->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		pLight6->getComponent<OluxEngine::PointLight>()->setPosition(glm::vec3(-19.0f, 8.0f, 16.0f));

		// //-------------------------------------------Environment
		// std::shared_ptr<OluxEngine::Entity> environment = core->addEntity();
		// environment->addComponent<Environment>("resources/environment.obj");

		// std::shared_ptr<OluxEngine::Texture> envTexture = core->getResources()->Load<OluxEngine::Texture>("resources/environment.png");
		// environment->getComponent<OluxEngine::MeshRenderer>()->setTexture(envTexture);

		// //-------------------------------------------Player
		// std::shared_ptr<OluxEngine::Entity> collectable = core->addEntity();
		// collectable->setTag("Collectable");
		// collectable->addComponent<OluxEngine::MeshRenderer>();
		// collectable->addComponent<OluxEngine::Transform>();
		// collectable->getComponent<OluxEngine::Transform>()->setLocalPosition(glm::vec3(-19.5f, -7.5, 23.5f));
		// std::shared_ptr<OluxEngine::Mesh> mesh = core->getResources()->Load<OluxEngine::Mesh>("resources/collectable.obj");
    	// collectable->getComponent<OluxEngine::MeshRenderer>()->setMesh(mesh);
		// std::shared_ptr<OluxEngine::Texture> tex = core->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
		// collectable->getComponent<OluxEngine::MeshRenderer>()->setTexture(tex);

		// std::shared_ptr<OluxEngine::Entity> player = core->addEntity();
		// player->addComponent<Player>("resources/curuthers.obj", "resources/curuthers_diffuse.png");
		
		//--------------------------------------------Start Game
		core->start(); 
	}
	catch(OluxEngine::Exception& e)
	{
		std::cout << "OluxEngine Exception: " << e.what() << std::endl;
	}
}