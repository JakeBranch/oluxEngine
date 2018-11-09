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

int main(int argc, char* argv[])
{
	try
	{
		std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

		std::shared_ptr<OluxEngine::Entity> entity = core->addEntity();

		std::shared_ptr<TestScene> ts = entity->addComponent<TestScene>();

		/*std::shared_ptr<OluxEngine::Sound> soundfx = core->getResources()->Load<OluxEngine::Sound>("dixie_horn.ogg");
		soundfx->play();*/
		
		//-------------------------------------------Player model
		std::shared_ptr<OluxEngine::MeshRenderer> mr = entity->addComponent<OluxEngine::MeshRenderer>("resources/curuthers.obj");
		mr->setShaders("resources/shaders/simple.vert", "resources/shaders/simple.frag");

		std::shared_ptr<OluxEngine::Texture> t = core->getResources()->Load<OluxEngine::Texture>("resources/curuthers_diffuse.png");
		mr->setTexture(t);

		//-------------------------------------------Castle model
		std::shared_ptr<OluxEngine::Entity> castle = core->addEntity();
		std::shared_ptr<OluxEngine::MeshRenderer> shape = castle->addComponent<OluxEngine::MeshRenderer>("resources/re_hall_baked.obj");
		shape->setShaders("resources/shaders/simple.vert", "resources/shaders/simple.frag");

		std::shared_ptr<OluxEngine::Texture> castleTexture = core->getResources()->Load<OluxEngine::Texture>("resources/re_hall_diffuse.png");
		shape->setTexture(castleTexture);

		core->Start();
	}
	catch(OluxEngine::Exception& e)
	{
		std::cout << "OluxEngine Exception: " << e.what() << std::endl;
	}

}