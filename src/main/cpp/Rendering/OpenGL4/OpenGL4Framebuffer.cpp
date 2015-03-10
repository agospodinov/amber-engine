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

            OpenGL4Framebuffer::OpenGL4Framebuffer(int dummy)
                : handle(0)
            {
            }

            OpenGL4Framebuffer::~OpenGL4Framebuffer()
            {
                glDeleteFramebuffers(1, &handle);
            }

            void OpenGL4Framebuffer::attach(IRenderTarget::AttachmentType type, Reference<ITexture> texture)
            {
                if (handle == 0)
                {
                    throw std::runtime_error("Cannot modify backbuffer");
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
