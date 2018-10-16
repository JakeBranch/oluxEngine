#include "Component.h"
#include "Resources.h"
#include "Texture.h"

#include <memory>

#include <glm/ext.hpp>

namespace OluxEngine
{
    class VertexArray;
    class ShaderProgram;

    class MeshRenderer : public Component
    {
        public:
            void onInit();
			void setTexture(std::shared_ptr<Texture> t);

        private:
            void onDisplay();

            std::shared_ptr<VertexArray> shape;
            std::shared_ptr<ShaderProgram> shader;
			std::shared_ptr<Resources> resources;
			std::shared_ptr<Texture> texture;
    
            float angle;
    };
}