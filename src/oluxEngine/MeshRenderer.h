#include "Component.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Mesh.h"
#include "Transform.h"

#include <memory>
#include <vector>
#include <string>

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
            void onInit();
			void setTexture(std::shared_ptr<Texture> t);
            void setShaders(std::string vertShader, std::string fragShader);

            std::shared_ptr<Material> getMaterial();

            void setMesh(std::shared_ptr<Mesh> mesh);
            
        private:
            void onDisplay();

            std::shared_ptr<Mesh> mesh;

            /**
            * Vertex array of the mesh
            */ 
            std::shared_ptr<VertexArray> shape;

            /**
            * Material of the mesh
            */
            std::shared_ptr<Material> material;
    };
}