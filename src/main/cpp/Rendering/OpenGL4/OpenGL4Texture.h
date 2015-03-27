#ifndef OPENGL4TEXTURE_H
#define OPENGL4TEXTURE_H

#include "Rendering/ITexture.h"

#include <cstdlib>
#include <cstdint>

#include <GL/gl.h>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Texture : public ITexture
            {
                public:
                    enum class GLType : GLenum
                    {
                        Texture1D = GL_TEXTURE_1D,
                        Texture2D = GL_TEXTURE_2D,
                        Texture3D = GL_TEXTURE_3D,
                        CubeMap = GL_TEXTURE_CUBE_MAP
                    };

                    OpenGL4Texture(Type type);
                    OpenGL4Texture(GLType type, std::size_t width, std::size_t height = 0, std::size_t depth = 0, std::size_t mipMapLevels = 1, const uint8_t *data = nullptr, DataMode mode = DataMode::RGBA);
                    OpenGL4Texture(const OpenGL4Texture &other) = delete;
                    OpenGL4Texture(OpenGL4Texture &&other) noexcept;
                    virtual ~OpenGL4Texture();

                    OpenGL4Texture &operator =(const OpenGL4Texture &other) = delete;
                    OpenGL4Texture &operator =(OpenGL4Texture &&other) noexcept;

                    virtual void bind() override final;
                    virtual void unbind() override final;

                    virtual BindType getBindType() const override final;
                    virtual std::uint32_t getBindSlot() const override final;
                    virtual void setBindSlot(std::uint32_t bindSlot) override final;

                    virtual std::size_t getWidth() const override final;
                    virtual std::size_t getHeight() const override final;
                    virtual std::size_t getDepth() const override final;

                    virtual Type getType() const override final;

                    virtual void setSize(std::size_t width = 0, std::size_t height = 0, std::size_t depth = 0) override final;

                    virtual void setImageData(DataMode mode, const uint8_t *data) override final;
                    virtual void setFilterMode(FilterMode mode) override final;
                    virtual void setWrapMode(WrapMode mode) override final;

                private:
                    GLuint handle;
                    GLType type;
                    std::size_t width;
                    std::size_t height;
                    std::size_t depth;
                    std::size_t mipMapLevels;
                    std::uint32_t bindSlot;
                    bool bound;
            };
        }
    }
}

#endif // OPENGL4TEXTURE_H
