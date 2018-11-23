#include "Component.h"
#include "Face.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Entity.h"
#include "Exception.h"

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <cmath>

namespace OluxEngine
{
    struct Extent
    {
        glm::vec3 max;
        glm::vec3 min;
    };

    struct ColliderColumn
    {
        glm::vec3 position;
        glm::vec3 size;
        std::vector<Face> faces;

        bool isColliding(glm::vec3 position, glm::vec3 size);
    };

    class StaticModelCollider : public Component
    {
        public:
            void onInit();
            Extent getExtent();
            bool isColliding(glm::vec3 position, glm::vec3 size);

            glm::vec3 getCollisionResponse(glm::vec3 position, glm::vec3 lastPosition, glm::vec3 size, bool& solved);
    
        private:
            std::vector<std::shared_ptr<ColliderColumn>> cols;
            Extent extent;

            float resolution;
            float tryStep;
            float maxStep;
            float tryInc;
            float maxInc;

            void generateExtent(std::vector<Face> meshFaces);
            void addFace(Face);
    };
}