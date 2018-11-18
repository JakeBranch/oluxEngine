#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <oluxEngine\OluxEngine.h>

#include <string>

class Environment : public OluxEngine::Component
{
	public:
		void onInit(std::string meshLoc);
		void onBegin();
		void update();
};

#endif