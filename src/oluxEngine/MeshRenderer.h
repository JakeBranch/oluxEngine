#include "Component.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <memory>

#include <glm/ext.hpp>

#include "Exception.h"

namespace OluxEngine
{
    class VertexArray;
    class ShaderProgram;

    /**
    * Class for loading/creating a mesh.
    */
    class MeshRenderer : public Component
    {
        public:
            void onInit(std::string meshLoc);
			void setTexture(std::shared_ptr<Texture> t);
            void setShaders(std::string vertShader, std::string fragShader);

            std::shared_ptr<Material> getMaterial();
            
        private:
            void onDisplay();

            /**
            * Vertex array of the mesh
            */ 
            std::shared_ptr<VertexArray> shape;

            /**
            * Shader attached to mesh
            */
            std::shared_ptr<ShaderProgram> shader;

            /**
            * Texture attached to mesh
            */
			std::shared_ptr<Texture> texture;

            /**
            * Material of the mesh
            */
            std::shared_ptr<Material> material;

            std::shared_ptr<DirectionalLight> dirLight;
            std::shared_ptr<PointLight> pointLight;
            std::shared_ptr<SpotLight> spotLight;
    
            float angle;
    };
}