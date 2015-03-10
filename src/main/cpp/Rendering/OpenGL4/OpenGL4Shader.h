#ifndef OPENGL4SHADER_H
#define OPENGL4SHADER_H

#include "Rendering/IShader.h"

#include <string>

#include <GL/gl.h>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Shader : public IShader
            {
                public:
                    enum class GLType : GLenum
                    {
                        Vertex = GL_VERTEX_SHADER,
                        Fragment = GL_FRAGMENT_SHADER,
                        Geometry = GL_GEOMETRY_SHADER
                    };

                    OpenGL4Shader(Type type);
                    OpenGL4Shader(GLType type, std::string shaderSource = std::string());
                    OpenGL4Shader(const OpenGL4Shader &other) = delete;
                    OpenGL4Shader(OpenGL4Shader &&other) noexcept;
                    virtual ~OpenGL4Shader();

                    OpenGL4Shader &operator =(const OpenGL4Shader &other) = delete;
                    OpenGL4Shader &operator =(OpenGL4Shader &&other) noexcept;

                    virtual void compile() override final;
                    virtual bool isCompiled() const override final;

                    virtual void setShaderSource(std::string shaderSource) override final;

                    virtual Language getLanguage() const override final;
                    virtual Type getType() const override final;

                    GLType getGLType() const;

                    friend bool operator==(const OpenGL4Shader &lhs, const OpenGL4Shader &rhs);

                private:
                    friend class OpenGL4Program;

                    GLuint handle;
                    GLType type;
                    bool compiled;
            };
        }
    }
}

#endif // OPENGL4SHADER_H
