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

    glm::vec3 Mesh::getSize()
    {
        std::vector<glm::vec3> positions;
       
        for(size_t f = 0; f < getFaces().size(); f++)
        {
            Face face = getFaces().at(f);
            positions.push_back(face.a.position);
            positions.push_back(face.b.position);
            positions.push_back(face.c.position);
        }

        glm::vec3 max;
        glm::vec3 min;
        max = positions.at(0);
        min = positions.at(0);

        for(size_t i = 1; i < positions.size(); i++)
        {
            if(positions.at(i).x > max.x) max.x = positions.at(i).x;
            if(positions.at(i).y > max.y) max.y = positions.at(i).y;
            if(positions.at(i).z > max.z) max.z = positions.at(i).z;
            if(positions.at(i).x < min.x) min.x = positions.at(i).x;
            if(positions.at(i).y < min.y) min.y = positions.at(i).y;
            if(positions.at(i).z < min.z) min.z = positions.at(i).z;
        }

        min.x -= 1;
        min.y -= 1;
        min.z -= 1;

        max.x += 1;
        max.y += 1;
        max.z += 1;

        glm::vec3 size = max - min;

        return size;
    }
}