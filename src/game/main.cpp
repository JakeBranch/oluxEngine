#include <oluxEngine/OluxEngine.h>
#include <glm/glm.hpp>

#include <cstdio>
#include <iostream>
#include <memory>

#include <exception>

#include <GL\glew.h>

#include <SDL.h>

#include <SDL_opengl.h>

#include "MainMenu.h"
#include "Environment.h"
#include "Player.h"

int main(int argc, char* argv[])
{
	try
	{
		std::shared_ptr<OluxEngine::Core> core = OluxEngine::Core::initialise();

		//------------------------------------------Load main menu
		std::shared_ptr<OluxEngine::Entity> mainMenu = core->addEntity();
		mainMenu->addComponent<MainMenu>();
		
		//--------------------------------------------Start Game
		core->start(); 
	}
	catch(OluxEngine::Exception& e)
	{
		std::cout << "OluxEngine Exception: " << e.what() << std::endl;
	}
}