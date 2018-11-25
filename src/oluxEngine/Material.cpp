#include "Material.h"

namespace OluxEngine
{
    Material::Material()
    {
        ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        specular = glm::vec3(0.5f, 0.5f, 0.5f);
        shininess = 32.0f;
    }

    void Material::setAmbient(glm::vec3 val)
    {
        ambient = val;
    }

    void Material::setSpecular(glm::vec3 val)
    {
        specular = val;
    }

    void Material::setShininess(float val)
    {
        shininess = val;
    }

    void Material::setShader(std::shared_ptr<ShaderProgram> program)
    {
        shader = program;
    }

    void Material::setDiffuse(std::shared_ptr<Texture> tex)
    {
        diffuse = tex;
    }

    glm::vec3 Material::getAmbient()
    {
        return ambient;
    }

    std::shared_ptr<Texture> Material::getDiffuse()
    {
        return diffuse;
    }

    glm::vec3 Material::getSpecular()
    {
        return specular;
    }

    float Material::getShininess()
    {
        return shininess;
    }

    std::shared_ptr<ShaderProgram> Material::getShader()
    {
        return shader;
    }
}