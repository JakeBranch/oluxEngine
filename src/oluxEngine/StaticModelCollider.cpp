#include "StaticModelCollider.h"
#include <iostream>

int triBoxOverlap(float boxcenter[3],
  float boxhalfsize[3],float triverts[3][3]);

namespace OluxEngine
{
    void StaticModelCollider::onInit()
    {
        resolution = 10.0f;
        maxStep = 1.0f;
        tryInc = 0.01f;
        maxInc = 0.5f;
        tryStep = 0.001f;

        std::shared_ptr<MeshRenderer> mr = getEntity()->getComponent<MeshRenderer>();
        std::shared_ptr<Mesh> mesh = mr->getMesh();

        std::vector<Face> meshFaces = mesh->getFaces();

        generateExtent(meshFaces);

        glm::vec3 size = extent.max - extent.min;
        glm::vec3 colSize = size / resolution;
        colSize.y = size.y;

        for(size_t y = 0; y < resolution; y++)
        {
            glm::vec3 pos = extent.min + colSize / 2.0f;
            pos.z += (float)y * colSize.z;

            for(size_t x = 0; x < resolution; x++)
            {
                std::shared_ptr<ColliderColumn> cc = std::make_shared<ColliderColumn>();
                cc->size = colSize;
                cc->position = pos;

                cols.push_back(cc);

                pos.x += colSize.x;
            }
        }

        for(size_t f = 0; f < meshFaces.size(); f++)
        {
            Face face = meshFaces.at(f);
            addFace(face);
        }
    }

    void StaticModelCollider::generateExtent(std::vector<Face> meshFaces)
    {
        std::vector<glm::vec3> positions;
       
        for(size_t f = 0; f < meshFaces.size(); f++)
        {
            Face face = meshFaces.at(f);
            positions.push_back(face.a.position);
            positions.push_back(face.b.position);
            positions.push_back(face.c.position);
        }

        extent.max = positions.at(0);
        extent.min = positions.at(0);

        for(size_t i = 1; i < positions.size(); i++)
        {
            if(positions.at(i).x > extent.max.x) extent.max.x = positions.at(i).x;
            if(positions.at(i).y > extent.max.y) extent.max.y = positions.at(i).y;
            if(positions.at(i).z > extent.max.z) extent.max.z = positions.at(i).z;
            if(positions.at(i).x < extent.min.x) extent.min.x = positions.at(i).x;
            if(positions.at(i).y < extent.min.y) extent.min.y = positions.at(i).y;
            if(positions.at(i).z < extent.min.z) extent.min.z = positions.at(i).z;
        }

        extent.min.x -= 1;
        extent.min.y -= 1;
        extent.min.z -= 1;

        extent.max.x += 1;
        extent.max.y += 1;
        extent.max.z += 1;
    }

    void StaticModelCollider::addFace(Face face)
    {
        float f[3][3] = {0};
        f[0][0] = face.a.position.x;
        f[0][1] = face.a.position.y;
        f[0][2] = face.a.position.z;
        f[1][0] = face.b.position.x;
        f[1][1] = face.b.position.y;
        f[1][2] = face.b.position.z;
        f[2][0] = face.c.position.x;
        f[2][1] = face.c.position.y;
        f[2][2] = face.c.position.z;

        bool found = false;

        for(size_t i = 0; i < cols.size(); i++)
        {
            float bc[3] = {0};
            bc[0] = cols.at(i)->position.x;
            bc[1] = cols.at(i)->position.y;
            bc[2] = cols.at(i)->position.z;

            glm::vec3 s = cols.at(i)->size;
            s.x += 1;
            s.z += 1;

            float bhs[3] = {0};
            bhs[0] = s.x / 2.0f;
            bhs[1] = s.y / 2.0f;
            bhs[2] = s.z / 2.0f;

            if(triBoxOverlap(bc, bhs, f))
            {
                cols.at(i)->faces.push_back(face);
                //std::cout << "Pushing face into " << i << std::endl;
                found = true;
            }
        }

        if(!found)
        {
            throw Exception("Face not assigned spatial partition");
        }
    }

    bool ColliderColumn::isColliding(glm::vec3 position, glm::vec3 size)
    {
        for(std::vector<Face>::iterator i = faces.begin(); i != faces.end(); i++)
        {
            float f[3][3] = {0};
            f[0][0] = i->a.position.x;
            f[0][1] = i->a.position.y;
            f[0][2] = i->a.position.z;
            f[1][0] = i->b.position.x;
            f[1][1] = i->b.position.y;
            f[1][2] = i->b.position.z;
            f[2][0] = i->c.position.x;
            f[2][1] = i->c.position.y;
            f[2][2] = i->c.position.z;

            float bc[3] = {0};
            bc[0] = position.x;
            bc[1] = position.y;
            bc[2] = position.z;
            float bhs[3] = {0};
            bhs[0] = size.x / 2.0f;
            bhs[1] = size.y / 2.0f;
            bhs[2] = size.z / 2.0f;

            if(triBoxOverlap(bc, bhs, f))
            {
                return true;
            }
        }

        return false;
    }

    bool StaticModelCollider::isColliding(glm::vec3 position, glm::vec3 size)
    {
        glm::vec3 pos = position - extent.min;
        size_t x = (size_t)(pos.x / cols.at(0)->size.x);
        size_t y = (size_t)(pos.z / cols.at(0)->size.z);
        size_t idx = y * resolution + x;

        if(idx >= cols.size()) return false;

        if(cols.at(idx)->isColliding(position, size))
        {
            return true;
        }

        return false;
    }

    glm::vec3 StaticModelCollider::getCollisionResponse(glm::vec3 position, glm::vec3 lastPosition, glm::vec3 size, bool& solved)
    {
        glm::vec3 diff = position - lastPosition;
        float len = fabs(diff.x) + fabs(diff.y) + fabs(diff.z);

        glm::vec3 solve = position;
        float amount = tryStep;

        solved = true;

        if(!isColliding(solve, size)) return solve;

        solved = true;

        while(true)
        {
            solve.y += amount;

            if(!isColliding(solve, size)) break;

            solve.y -= amount;
            amount += tryStep;

            if(amount > maxStep)
            {
                solved = false;
                break;
            }
        }

        if(solved) return solve;

        solved = true;
        amount = tryInc;

        while(true)
        {
            //if(!isColliding(solve, size)) break;
            solve.x += amount;
            if(!isColliding(solve, size)) break;
            solve.x -= amount;
            solve.x -= amount;
            if(!isColliding(solve, size)) break;
            solve.x += amount;
            solve.z += amount;
            if(!isColliding(solve, size)) break;
            solve.z -= amount;
            solve.z -= amount;
            if(!isColliding(solve, size)) break;
            solve.z += amount;
            amount += tryInc;

            if(amount > maxInc)
            {
                solved = false;
                break;
            }
        }

        if(solved) return solve;
        solved = true;
        amount = tryInc;

        // Attempt to uncollide in x/z/y (walls + steps)
        while(true)
        {
            solve.y = lastPosition.y;
            solve.x += amount;
            if(!isColliding(solve, size)) break;
            solve.x -= amount;
            solve.x -= amount;
            if(!isColliding(solve, size)) break;
            solve.x += amount;
            solve.z += amount;
            if(!isColliding(solve, size)) break;
            solve.z -= amount;
            solve.z -= amount;
            if(!isColliding(solve, size)) break;
            solve.z += amount;
            solve.y = position.y;
            amount += tryInc;

            if(amount > maxInc)
            {
                solved = false;
                break;
            }
        }

        if(solved) return solve;
        
        solved = true;
        amount = tryInc;

        // Attempt to uncollide in x+z (corners)
        while(true)
        {
            //if(!isColliding(solve, size)) break;
            solve.x -= amount; // TL
            solve.z += amount;
            if(!isColliding(solve, size)) break;
            solve.x += amount; // TR
            solve.x += amount;
            if(!isColliding(solve, size)) break;
            solve.z -= amount; // BR
            solve.z -= amount;
            if(!isColliding(solve, size)) break;
            solve.x -= amount; // BL
            solve.x -= amount;
            if(!isColliding(solve, size)) break;
            solve.z += amount;
            solve.x += amount;
            amount += tryInc;

            if(amount > maxInc)
            {
            solved = false;
            break;
            }
        }

        if(solved) return solve;
        solved = true;
        amount = tryInc;

        // Attempt to uncollide in x+z/y (corners + steps)
        while(true)
        {
            //if(!isColliding(solve, size)) break;
            solve.y = lastPosition.y;
            solve.x -= amount; // TL
            solve.z += amount;
            if(!isColliding(solve, size)) break;
            solve.x += amount; // TR
            solve.x += amount;
            if(!isColliding(solve, size)) break;
            solve.z -= amount; // BR
            solve.z -= amount;
            if(!isColliding(solve, size)) break;
            solve.x -= amount; // BL
            solve.x -= amount;
            if(!isColliding(solve, size)) break;
            solve.z += amount;
            solve.x += amount;
            solve.y = position.y;
            amount += tryInc;

            if(amount > maxInc)
            {
            solved = false;
            break;
            }
        }

        return solve;
    }
}
