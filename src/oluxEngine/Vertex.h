#ifndef OLUXENGINE_VERTEX_H
#define OLUXENGINE_VERTEX_H

#include <glm/glm.hpp>

namespace OluxEngine
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
    };
}

#endif