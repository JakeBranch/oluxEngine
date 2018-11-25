#ifndef OLUXENGINE_MESHRENDERER_H
#define OLUXENGINE_MESHRENDERER_H

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
#include <list>
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
            void setMesh(std::shared_ptr<Mesh> mesh);

            std::shared_ptr<Material> getMaterial();
            std::shared_ptr<Mesh> getMesh();
            
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

#endif