#ifndef OLUXENGINE_FACE_H
#define OLUXENGINE_FACE_H

#include "Vertex.h"

namespace OluxEngine
{
    struct Face
    {
        Vertex a;
        Vertex b;
        Vertex c;
    };
}

#endif