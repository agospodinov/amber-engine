#ifndef OPENGL4FRAMEBUFFER_H
#define OPENGL4FRAMEBUFFER_H

#include "Rendering/IRenderTarget.h"

#include <cstdint>

#include <GL/gl.h>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Framebuffer : public IRenderTarget
            {
                public:
                    OpenGL4Framebuffer();
                    virtual ~OpenGL4Framebuffer();

                    virtual void attach(AttachmentType type, Reference<ITexture> texture) override final;

                    virtual void bind() override final;
                    virtual void unbind() override final;

                    virtual BindType getBindType() const override final;
                    virtual std::uint32_t getBindSlot() const override final;

                private:
                    friend class OpenGL4Context;
                    OpenGL4Framebuffer(int dummy);

                    GLuint handle;
            };
        }
    }
}

#endif // OPENGL4FRAMEBUFFER_H
