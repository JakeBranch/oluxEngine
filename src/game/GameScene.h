#include <iostream>
#include <oluxEngine\OluxEngine.h>

#include <memory>

class GameScene : public OluxEngine::Component
{
	public:
		void onInit();
        void onGui();
};