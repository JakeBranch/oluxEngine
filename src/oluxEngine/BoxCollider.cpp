#include "BoxCollider.h"

namespace OluxEngine 
{
    void BoxCollider::onInit()
    {

    }
    
    bool BoxCollider::isColliding(glm::vec3 playerPos, glm::vec3 objPos, glm::vec3 objSize)
    {
        if(playerPos.x > objPos.x && playerPos.x < objPos.x + objSize.x)
        {
            if(playerPos.y > objPos.y && playerPos.y < objPos.y + objSize.y)
            {
                if(playerPos.z > objPos.z && playerPos.z < objPos.z + objSize.z)
                {
                    return true;
                }
            }
        }

        return false;
    }
}