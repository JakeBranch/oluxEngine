#include "Component.h"
#include "Resources.h"
#include "Texture.h"

#include <memory>

#include <glm/ext.hpp>

#include "Exception.h"

namespace OluxEngine
{
    class VertexArray;
    class ShaderProgram;

    class MeshRenderer : public Component
    {
        public:
            void onInit(std::string meshLoc);
			void setTexture(std::shared_ptr<Texture> t);
            void setShaders(std::string vertShader, std::string fragShader);

        private:
            void onDisplay();

            std::shared_ptr<VertexArray> shape;
            std::shared_ptr<ShaderProgram> shader;
			std::shared_ptr<Resources> resources;
			std::shared_ptr<Texture> texture;
    
            float angle;
    };
}