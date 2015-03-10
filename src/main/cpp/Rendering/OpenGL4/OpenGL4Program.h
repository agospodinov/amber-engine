#ifndef OPENGL4PROGRAM_H
#define OPENGL4PROGRAM_H

#include "Rendering/IProgram.h"

#include <memory>
#include <vector>

#include <GL/gl.h>

#include "Rendering/Layout.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Shader;

            class OpenGL4Program : public IProgram
            {
                public:
                    OpenGL4Program();
                    OpenGL4Program(const OpenGL4Program &other) = delete;
                    OpenGL4Program(OpenGL4Program &&other) noexcept;
                    virtual ~OpenGL4Program();

                    OpenGL4Program &operator =(const OpenGL4Program &other) = delete;
                    OpenGL4Program &operator =(OpenGL4Program &&other) noexcept;

                    virtual void bind() override final;
                    virtual void unbind() override final;

                    virtual BindType getBindType() const override final;
                    virtual std::uint32_t getBindSlot() const;

                    virtual void link() override final;
                    virtual bool isLinked() const override final;

                    const std::vector<Reference<OpenGL4Shader>> &getShaders() const;
                    virtual void addShader(Reference<IShader> shader) override final;

                    virtual const std::shared_ptr<Layout> &getLayout() const override final;
                    virtual void setLayout(std::shared_ptr<Layout> layout) override final;

                    virtual void setConstant(std::string name, std::int32_t value) override final;
                    virtual void setConstant(std::string name, std::uint32_t value) override final;
                    virtual void setConstant(std::string name, float value)  override final;

                    virtual void setConstant(std::string name, Eigen::Matrix4f value)  override final;
                    virtual void setConstant(std::string name, Eigen::Vector2f value)  override final;
                    virtual void setConstant(std::string name, Eigen::Vector3f value)  override final;
                    virtual void setConstant(std::string name, Eigen::Vector4f value)  override final;

                private:
                    void introspect();
                    GLint findConstantByName(const std::string &name);

                    GLuint handle;
                    std::vector<Reference<OpenGL4Shader>> shaders;
                    std::shared_ptr<Layout> layout;
                    bool linked;
            };
        }
    }
}

#endif // OPENGL4PROGRAM_H
