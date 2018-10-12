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
	std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

	std::shared_ptr<OluxEngine::Entity> entity = core->addEntity();
	
	// std::shared_ptr<OluxEngine::Sound> s = std::make_shared<OluxEngine::Sound>("dixie_horn.ogg");
  	// s->play();

	std::shared_ptr<TestScene> ts = entity->addComponent<TestScene>();

	std::shared_ptr<OluxEngine::Texture> t = core->getResources()->Load<OluxEngine::Texture>("resources/texture.png");

	std::shared_ptr<OluxEngine::Sound> soundfx = core->getResources()->Load<OluxEngine::Sound>("dixie_horn.ogg");
	soundfx->play();

	std::shared_ptr<OluxEngine::MeshRenderer> mr = entity->addComponent<OluxEngine::MeshRenderer>();
	mr->onInit();
	mr->setTexture(t);

	core->Start();
}