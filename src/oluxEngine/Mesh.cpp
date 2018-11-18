#include "Mesh.h"

namespace OluxEngine
{
    std::shared_ptr<Mesh> Mesh::Load(std::string path)
	{
        std::shared_ptr<Mesh> rtn = std::make_shared<Mesh>();
        rtn->shape = std::make_shared<VertexArray>(path);

        return rtn;
    }

    std::shared_ptr<VertexArray> Mesh::getShape()
    {
        return shape;
    }

    std::vector<Face> Mesh::getFaces()
	{
		return shape->getFaces();
	}
}