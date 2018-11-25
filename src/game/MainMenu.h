#include <iostream>
#include <oluxEngine\OluxEngine.h>

class MainMenu : public OluxEngine::Component
{
	public:
        void onGui();
        
        void play();
};