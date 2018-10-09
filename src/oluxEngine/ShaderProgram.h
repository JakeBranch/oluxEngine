#include "Resource.h"

#include <GL/glew.h>
#include <glm.hpp>

#include <string>
#include <memory>

namespace OluxEngine
{
    class VertexArray;

    class ShaderProgram : public Resource
    {
        GLuint id;
        std::string ReadFile(const char* fileLocation);
        void CompileShader(const char* vertCode, const char* fragCode);
        void AddShader(GLuint program, const char* code, GLenum type);

        public:
			static std::shared_ptr<ShaderProgram> Load(const char* vertLoc, const char* fragLoc);
			static std::shared_ptr<ShaderProgram> Create(const char* vertCode, const char* fragCode);

			ShaderProgram();
            //ShaderProgram(const char* vertLoc, const char* fragLoc);
            void Draw(VertexArray &VertexArray);
            void SetUniform(std::string uniform, glm::vec4 val);
            void SetUniform(std::string uniform, glm::mat4 val);
            void SetUniform(std::string uniform, float val);
            GLuint getId();
    };
}