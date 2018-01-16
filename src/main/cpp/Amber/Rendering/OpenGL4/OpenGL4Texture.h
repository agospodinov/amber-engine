#ifndef OPENGL4TEXTURE_H
#define OPENGL4TEXTURE_H

#include "Amber/Rendering/ITexture.h"
#include "Amber/Rendering/OpenGL4/OpenGL4Object.h"

#include <cstdlib>
#include <cstdint>

#include "Amber/Rendering/OpenGL4/OpenGL4Includes.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Texture : public ITexture, public OpenGL4Object
            {
                public:
                    OpenGL4Texture(Type type, DataFormat dataFormat, std::size_t width = 0, std::size_t height = 0, std::size_t depth = 0, std::size_t mipMapLevels = 1, const uint8_t *data = nullptr);
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

                    virtual void setImageData(const uint8_t *data) override final;
                    virtual void setFilterMode(FilterMode mode) override final;
                    virtual void setWrapMode(WrapMode mode) override final;

                private:
                    GLenum getGLType(Type type) const;
                    GLenum getGLInternalFormat(DataFormat format) const;
                    GLenum getGLFormat(DataFormat format) const;
                    GLenum getGLPixelType(DataFormat dataFormat) const;
                    std::size_t getChannels(DataFormat dataFormat) const;

                    Type type;
                    DataFormat dataFormat;
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
