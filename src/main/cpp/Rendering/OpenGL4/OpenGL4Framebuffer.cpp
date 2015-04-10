#include "OpenGL4Framebuffer.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Framebuffer::OpenGL4Framebuffer()
            {
                glGenFramebuffers(1, &handle);
            }

            OpenGL4Framebuffer::OpenGL4Framebuffer(OpenGL4Framebuffer &&other) noexcept
                : OpenGL4Object(other.handle)
            {
                other.handle = 0;
            }

            OpenGL4Framebuffer::OpenGL4Framebuffer(int dummy)
                : OpenGL4Object(0)
            {
            }

            OpenGL4Framebuffer::~OpenGL4Framebuffer()
            {
                if (handle != 0)
                {
                    glDeleteFramebuffers(1, &handle);
                }
            }

            OpenGL4Framebuffer &OpenGL4Framebuffer::operator =(OpenGL4Framebuffer &&other) noexcept
            {
                if (this != &other)
                {
                    handle = other.handle;

                    other.handle = 0;
                }

                return *this;
            }

            void OpenGL4Framebuffer::attach(IRenderTarget::AttachmentType type, Reference<ITexture> texture)
            {
                if (handle == 0)
                {
                    throw std::runtime_error("Invalid framebuffer or attempting to modify backbuffer.");
                }

                bind();
//                glFramebufferTexture(GL_FRAMEBUFFER, type, texture->getHandle(), 0);
                unbind();
            }

            void OpenGL4Framebuffer::bind()
            {
                glBindFramebuffer(GL_FRAMEBUFFER, handle);
            }

            void OpenGL4Framebuffer::unbind()
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            IBindable::BindType OpenGL4Framebuffer::getBindType() const
            {
                return BindType::RenderTarget;
            }

            std::uint32_t OpenGL4Framebuffer::getBindSlot() const
            {
                return 0;
            }

        }
    }
}
