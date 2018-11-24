#ifndef OLUXENGINE_SHADERPROGRAM_H
#define OLUXENGINE_SHADERPROGRAM_H

#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>

#include "Exception.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "VertexBuffer.h"

namespace OluxEngine
{
    class VertexArray;

    struct Sampler
    {
        GLint id;
        std::shared_ptr<Texture> texture;
        std::shared_ptr<RenderTexture> renderTexture;
        bool isRenderTexture;
    };

    /**
    * Class which handles the loading, creation, and management of a shader program. 
    *
    * The class contains an ID pointing to the created shader program, functions to set uniform variables, and function for drawing.
    */
    class ShaderProgram : public Resource
    {
        /**
        *ID of shader program
        */
        GLuint id;
        std::vector<Sampler> samplers;
        glm::vec4 viewport;
        std::shared_ptr<VertexArray> simpleShape;

        public:
			static std::shared_ptr<ShaderProgram> Load(std::string vertLoc, std::string fragLoc);
			static std::shared_ptr<ShaderProgram> Create(const char* vertCode, const char* fragCode, const char* vertLoc, const char* fragLoc);

			ShaderProgram();
            void Draw();
            void Draw(std::shared_ptr<RenderTexture> renderTexture);
            void Draw(std::shared_ptr<VertexArray> vertexArray);
            void Draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray);
            void SetUniform(std::string uniform, glm::vec3 val);
            void SetUniform(std::string uniform, glm::vec4 val);
            void SetUniform(std::string uniform, glm::mat4 val);
            void SetUniform(std::string uniform, float val);
			void SetUniform(std::string uniform, int val);
            void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
            void SetUniform(std::string uniform, std::shared_ptr<RenderTexture> renderTexture);
            GLuint getId();
            void setViewport(glm::vec4 viewport);
    };
}

#endif