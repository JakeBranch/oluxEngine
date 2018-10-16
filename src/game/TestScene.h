#include <iostream>
#include <oluxEngine\OluxEngine.h>

class TestScene : public OluxEngine::Component
{
	public:
		void onInit();
		void onBegin();
		void update();
};