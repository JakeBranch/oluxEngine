#ifndef OLUXENGINE_GUI_H
#define OLUXENGINE_GUI_H

#include "ShaderProgram.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderProgram.h"

#include <memory>
#include <glm/glm.hpp>
#include <SDL.h>

namespace OluxEngine
{   
    class Core;

    class Gui
    {
        public:
        Gui(std::weak_ptr<Core> coreRef);
       
        void display();

        bool button(int xPos, int yPos, int width, int height, std::shared_ptr<Texture> tex);
        void image(int xPos, int yPos, int width, int height, std::shared_ptr<Texture> tex);

        std::shared_ptr<Texture> texture;
        std::shared_ptr<ShaderProgram> shader;

        std::weak_ptr<Core> core;
    };
}

#endif