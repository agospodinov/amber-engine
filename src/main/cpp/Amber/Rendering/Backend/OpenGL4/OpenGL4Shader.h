#ifndef OPENGL4SHADER_H
#define OPENGL4SHADER_H

#include "Amber/Rendering/Backend/IShader.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Object.h"

#include <string>

#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Includes.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Shader : public IShader, public OpenGL4Object
            {
                public:
                    OpenGL4Shader(Type type, std::string shaderSource = std::string());
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

                    friend bool operator==(const OpenGL4Shader &lhs, const OpenGL4Shader &rhs);

                private:
                    friend class OpenGL4Program;

                    GLenum getGLType(Type type) const;

                    Type type;
                    bool compiled;
            };
        }
    }
}

#endif // OPENGL4SHADER_H
