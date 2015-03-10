#include "OpenGL4Shader.h"

#include <fstream>
#include <stdexcept>
#include <vector>

#include <GL/gl.h>

#include "Utilities/Logger.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Shader::OpenGL4Shader(IShader::Type type)
                : handle(0),
                  compiled(false)
            {
                switch (type)
                {
                    case Type::VertexShader:
                        this->type = GLType::Vertex;
                        break;
                    case Type::PixelShader:
                        this->type = GLType::Fragment;
                        break;
                    default:
                        throw std::runtime_error("Unsupported shader type.");
                }

                handle = glCreateShader(static_cast<GLenum>(this->type));

                if (handle == 0)
                {
                    Utilities::Logger log;
                    GLenum error = glGetError();

                    log.fatal("Shader creation failed; error type: " + std::to_string(error));
                    throw std::runtime_error("Shader could not be created!");
                }
            }

            OpenGL4Shader::OpenGL4Shader(GLType type, std::string shaderSource)
                : handle(0),
                  type(type),
                  compiled(false)
            {
                handle = glCreateShader(static_cast<GLenum>(type));

                if (handle == 0)
                {
                    Utilities::Logger log;
                    GLenum error = glGetError();

                    log.fatal("Shader creation failed; error type: " + std::to_string(error));
                    throw std::runtime_error("Shader could not be created!");
                }

                if (!shaderSource.empty())
                {
                    setShaderSource(shaderSource);
                }
            }

            OpenGL4Shader::OpenGL4Shader(OpenGL4Shader &&other) noexcept
                : handle(other.handle),
                  type(other.type),
                  compiled(other.compiled)
            {
                other.handle = 0;
            }

            OpenGL4Shader::~OpenGL4Shader()
            {
                if (handle != 0)
                {
                    glDeleteShader(handle);
                }
            }

            OpenGL4Shader &OpenGL4Shader::operator =(OpenGL4Shader &&other) noexcept
            {
                if (this != &other)
                {
                    handle = other.handle;
                    type = other.type;
                    compiled = other.compiled;

                    other.handle = 0;
                }

                return *this;
            }

            void OpenGL4Shader::compile()
            {
                glCompileShader(handle);

                int compiled = 0;
                glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

                if (compiled == 0)
                {
                    Utilities::Logger log;

                    GLint length;
                    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);

                    std::vector<GLchar> compileLog(length);
                    glGetShaderInfoLog(handle, length, NULL, compileLog.data());

                    std::string compileLogStr(compileLog.begin(), compileLog.end());
                    log.fatal(compileLogStr);

                    throw std::runtime_error("Shader with ID " + std::to_string(handle) + ": compilation failed!");
                }

                this->compiled = true;
            }

            bool OpenGL4Shader::isCompiled() const
            {
                return compiled;
            }

            void OpenGL4Shader::setShaderSource(std::string shaderSource)
            {
                const char *code = shaderSource.c_str();
                const int length = static_cast<GLint>(shaderSource.length());

                glShaderSource(handle, 1, &code, &length);
            }

            IShader::Language OpenGL4Shader::getLanguage() const
            {
                return Language::GLSL;
            }

            IShader::Type OpenGL4Shader::getType() const
            {
                switch (type)
                {
                    case GLType::Vertex:
                        return Type::VertexShader;
                    case GLType::Fragment:
                        return Type::PixelShader;
                    default:
                        return Type::Other;
                }
            }

            OpenGL4Shader::GLType OpenGL4Shader::getGLType() const
            {
                return type;
            }

            bool operator==(const OpenGL4Shader &lhs, const OpenGL4Shader &rhs)
            {
                return lhs.handle == rhs.handle;
            }
        }
    }
}
