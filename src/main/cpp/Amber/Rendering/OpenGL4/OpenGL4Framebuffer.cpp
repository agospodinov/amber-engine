#include "OpenGL4Framebuffer.h"

#include "Amber/Utilities/Logger.h"
#include "OpenGL4Texture.h"

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

            void OpenGL4Framebuffer::attach(Reference<ITexture> texture, IRenderTarget::AttachmentType type, std::uint32_t index)
            {
                if (handle == 0)
                {
                    throw std::runtime_error("Invalid framebuffer or attempting to modify backbuffer.");
                }

                Reference<OpenGL4Texture> openGlTexture = texture.cast<OpenGL4Texture>();

                if (!openGlTexture.isValid())
                {
                    throw std::invalid_argument("Invalid texture.");
                }


                bind();
                glFramebufferTexture(GL_FRAMEBUFFER, getGLType(type, index), openGlTexture->getHandle(), 0);
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

            GLenum OpenGL4Framebuffer::getGLType(IRenderTarget::AttachmentType type, std::uint32_t index) const
            {
                if (type != AttachmentType::Color && index != 0)
                {
                    Utilities::Logger log;
                    log.warning("Framebuffer attachment index is " + std::to_string(index) + " but type is not Color.");
                }

                switch (type)
                {
                    case AttachmentType::Color:
                        return GL_COLOR_ATTACHMENT0 + index;
                    case AttachmentType::Depth:
                        return GL_DEPTH_ATTACHMENT;
                    case AttachmentType::Stencil:
                        return GL_STENCIL_ATTACHMENT;
                    case AttachmentType::DepthStencil:
                        return GL_DEPTH_STENCIL_ATTACHMENT;
                    default:
                        throw std::invalid_argument("Invalid attachment type.");
                }
            }
        }
    }
}
