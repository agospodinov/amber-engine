#include "OpenGL4VertexArray.h"

#include "Amber/Rendering/Backend/VertexTypes.h"
#include "OpenGL4Includes.h"
#include "OpenGL4Buffer.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4VertexArray::OpenGL4VertexArray(Reference<OpenGL4Buffer> vertexBuffer, Reference<OpenGL4Buffer> indexBuffer)
                : vertexBuffer(vertexBuffer),
                  indexBuffer(indexBuffer)
            {
                glGenVertexArrays(1, &handle);
            }

            OpenGL4VertexArray::OpenGL4VertexArray(OpenGL4VertexArray &&other) noexcept
                : OpenGL4Object(other.handle),
                  vertexBuffer(other.vertexBuffer),
                  indexBuffer(other.indexBuffer),
                  layout(std::move(other.layout))
            {
                other.handle = 0;
            }

            OpenGL4VertexArray::~OpenGL4VertexArray()
            {
                if (handle != 0)
                {
                    glDeleteVertexArrays(1, &handle);
                }
            }

            OpenGL4VertexArray &OpenGL4VertexArray::operator =(OpenGL4VertexArray &&other) noexcept
            {
                if (this != &other)
                {
                    handle = other.handle;
                    vertexBuffer = other.vertexBuffer;
                    indexBuffer = other.indexBuffer;
                    layout = std::move(other.layout);

                    other.handle = 0;
                }

                return *this;
            }

            void OpenGL4VertexArray::bind()
            {
                glBindVertexArray(handle);
            }

            void OpenGL4VertexArray::unbind()
            {
                glBindVertexArray(0);
            }

            IBindable::BindType OpenGL4VertexArray::getBindType() const
            {
                return BindType::VertexArray;
            }

            std::uint32_t OpenGL4VertexArray::getBindSlot() const
            {
                return 0;
            }

            bool OpenGL4VertexArray::hasIndexBuffer() const
            {
                return indexBuffer.isValid();
            }

            void OpenGL4VertexArray::reset(bool deleteNeeded)
            {
                if (deleteNeeded)
                {
                    // FIXME this doesn't seem like the best solution...
                    glDeleteVertexArrays(1, &handle);
                    glGenVertexArrays(1, &handle);
                }

                bind();
                vertexBuffer->bind();
                if (hasIndexBuffer())
                {
                    indexBuffer->bind();
                }

                std::size_t stride = layout.getTotalStride();
                for (std::size_t i = 0; i < layout.getAttributeCount(); i++)
                {
                    const Layout::Attribute &attribute = layout.getAttributes().at(i);
                    glVertexAttribPointer(i, // FIXME probably not proper
                                          attribute.getCount(),
                                          getGLComponentType(attribute.getType()),
                                          attribute.getType() != Layout::ComponentType::Float,
                                          stride,
                                          reinterpret_cast<const void *>(layout.getOffset(i)));
                    glEnableVertexAttribArray(i); // FIXME probably not proper
                }
                unbind();
            }

            GLenum OpenGL4VertexArray::getGLComponentType(Layout::ComponentType type) const
            {

                switch (type)
                {
                    case Layout::ComponentType::Float:
                        return GL_FLOAT;
                    case Layout::ComponentType::Double:
                        return GL_DOUBLE;
                    case Layout::ComponentType::Int8:
                        return GL_BYTE;
                    case Layout::ComponentType::Int16:
                        return GL_SHORT;
                    case Layout::ComponentType::Int32:
                        return GL_INT;
                    case Layout::ComponentType::UInt8:
                        return GL_UNSIGNED_BYTE;
                    case Layout::ComponentType::UInt16:
                        return GL_UNSIGNED_SHORT;
                    case Layout::ComponentType::UInt32:
                        return GL_UNSIGNED_INT;
                    default:
                        throw std::invalid_argument("Invalid component type");
                }
            }

            const Layout &OpenGL4VertexArray::getLayout() const
            {
                return layout;
            }

            void OpenGL4VertexArray::setLayout(Layout layout)
            {
                bool deleteNeeded = !this->layout.getAttributes().empty();
                this->layout = std::move(layout);
                reset(deleteNeeded);
            }
        }
    }
}
