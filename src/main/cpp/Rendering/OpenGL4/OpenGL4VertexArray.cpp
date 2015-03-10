#include "OpenGL4VertexArray.h"

#include <GL/gl.h>
#include <GL/glext.h>

#include "Rendering/VertexTypes.h"
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
                : handle(other.handle),
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

                std::size_t stride = layout->getAttributeStride();
                for (const auto &attribute : layout->getAttributes())
                {
                    const Vertex::Semantic &semantic = attribute.second;
                    glVertexAttribPointer(Layout::getStandardBindLocation(semantic),
                                          Vertex::componentCount(semantic),
                                          Vertex::componentType(semantic),
                                          (semantic == Vertex::Semantic::Colors) ? GL_TRUE : GL_FALSE,
                                          stride,
                                          reinterpret_cast<const void *>(Vertex::attributeOffset(semantic)));
                    glEnableVertexAttribArray(Layout::getStandardBindLocation(semantic));
                }
                unbind();
            }

            const std::shared_ptr<Layout> &OpenGL4VertexArray::getLayout() const
            {
                return layout;
            }

            void OpenGL4VertexArray::setLayout(std::shared_ptr<Layout> layout)
            {
                bool deleteNeeded = this->layout && !this->layout->getAttributes().empty();
                this->layout = std::move(layout);
                reset(deleteNeeded);
            }
        }
    }
}
