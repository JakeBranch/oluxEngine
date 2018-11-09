#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>

#include "Exception.h"
#include "Texture.h"

namespace OluxEngine
{
    class VertexArray;

    struct Sampler
    {
        GLint id;
        std::shared_ptr<Texture> texture;
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

        public:
			static std::shared_ptr<ShaderProgram> Load(const char* vertLoc, const char* fragLoc);
			static std::shared_ptr<ShaderProgram> Create(const char* vertCode, const char* fragCode, const char* vertLoc, const char* fragLoc);

			ShaderProgram();
            void Draw(VertexArray &VertexArray);
            void SetUniform(std::string uniform, glm::vec4 val);
            void SetUniform(std::string uniform, glm::mat4 val);
            void SetUniform(std::string uniform, float val);
			void SetUniform(std::string uniform, int val);
            void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
            GLuint getId();
    };
}