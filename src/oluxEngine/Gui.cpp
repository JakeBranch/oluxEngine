#include "Gui.h"
#include "Core.h"

namespace OluxEngine
{
    Gui::Gui(std::weak_ptr<Core> coreRef)
    {
        core = coreRef;
        std::shared_ptr<Core> tmp = core.lock();
        shader = tmp->getResources()->Load<ShaderProgram>("resources/shaders/nullpass.vert", "resources/shaders/nullpass.frag");
        texture = tmp->getResources()->Load<Texture>("resources/button2.png");
    }

    bool Gui::button(int xPos, int yPos, int width, int height, std::shared_ptr<Texture> tex)
    {
        std::shared_ptr<Core> tmp = core.lock();
        shader->setViewport(glm::vec4(xPos, yPos, width, height));
        shader->SetUniform("in_Texture", tex);
        shader->Draw();

        glm::vec2 mousePos = tmp->getMouse()->getPosition();

        float firstPercent = (mousePos.y / 800) * 100;
        float remainingPercent = 100 - firstPercent;

        mousePos.y = 800 * (remainingPercent / 100);

        if(tmp->getMouse()->getMouseButtonDown(SDL_BUTTON_LEFT))
        {
            if(mousePos.x > xPos && mousePos.x < (xPos + width))
            {
                if(mousePos.y > yPos && mousePos.y < (yPos + height))
                {
                    return true;
                }
            }
        }

        return false;
    }

    void Gui::image(int xPos, int yPos, int width, int height, std::shared_ptr<Texture> tex)
    {
        std::shared_ptr<Core> tmp = core.lock();
        shader->setViewport(glm::vec4(xPos, yPos, width, height));
        shader->SetUniform("in_Texture", tex);
        shader->Draw();
    }
}