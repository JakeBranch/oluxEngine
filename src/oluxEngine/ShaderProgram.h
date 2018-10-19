#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>

#include "Exception.h"

namespace OluxEngine
{
    class VertexArray;

    class ShaderProgram : public Resource
    {
        GLuint id;

        public:
			static std::shared_ptr<ShaderProgram> Load(const char* vertLoc, const char* fragLoc);
			static std::shared_ptr<ShaderProgram> Create(const char* vertCode, const char* fragCode, const char* vertLoc, const char* fragLoc);

			ShaderProgram();
            //ShaderProgram(const char* vertLoc, const char* fragLoc);
            void Draw(VertexArray &VertexArray);
            void SetUniform(std::string uniform, glm::vec4 val);
            void SetUniform(std::string uniform, glm::mat4 val);
            void SetUniform(std::string uniform, float val);
			void SetUniform(std::string uniform, int val);
            GLuint getId();
    };
}