#include <iostream>
#include <oluxEngine\OluxEngine.h>

class MainMenu : public OluxEngine::Component
{
	public:
		void onInit();
        void onGui();
        
        void play();
};