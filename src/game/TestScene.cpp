#include "TestScene.h"

void TestScene::onBegin()
{
	std::cout << "onBegin" << std::endl;
}

void TestScene::onInit()
{
	std::cout << "onInit" << std::endl;
}

void TestScene::onUpdate()
{
	if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_W))
	{
		if(getCore()->getKeyboard()->getKeyDown(SDL_SCANCODE_LSHIFT))
		{
			std::cout << "FUCK YEAH" << std::endl;
		}
	}
}