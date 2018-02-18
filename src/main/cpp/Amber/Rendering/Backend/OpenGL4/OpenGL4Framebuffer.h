#ifndef OPENGL4FRAMEBUFFER_H
#define OPENGL4FRAMEBUFFER_H

#include "Amber/Rendering/Backend/IRenderTarget.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Object.h"

#include <cstdint>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Framebuffer : public IRenderTarget, public OpenGL4Object
            {
                public:
                    OpenGL4Framebuffer();
                    OpenGL4Framebuffer(const OpenGL4Framebuffer &other) = delete;
                    OpenGL4Framebuffer(OpenGL4Framebuffer &&other) noexcept;
                    virtual ~OpenGL4Framebuffer();

                    OpenGL4Framebuffer &operator =(const OpenGL4Framebuffer &other) = delete;
                    OpenGL4Framebuffer &operator =(OpenGL4Framebuffer &&other) noexcept;

                    virtual void attach(Reference<ITexture> texture, AttachmentType type, std::uint32_t index = 0) override final;

                    virtual void bind() override final;
                    virtual void unbind() override final;

                    virtual BindType getBindType() const override final;
                    virtual std::uint32_t getBindSlot() const override final;

                private:
                    friend class OpenGL4Context;
                    OpenGL4Framebuffer(int dummy);

                    GLenum getGLType(AttachmentType type, std::uint32_t index) const;
            };
        }
    }
}

#endif // OPENGL4FRAMEBUFFER_H
