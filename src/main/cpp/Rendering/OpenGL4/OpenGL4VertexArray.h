#ifndef OPENGL4VERTEXARRAY_H
#define OPENGL4VERTEXARRAY_H

#include "Rendering/IBindable.h"

#include <GL/gl.h>

#include "Rendering/Layout.h"
#include "Rendering/Reference.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Buffer;

            class OpenGL4VertexArray : public IBindable
            {
                public:
                    OpenGL4VertexArray(Reference<OpenGL4Buffer> vertexBuffer, Reference<OpenGL4Buffer> indexBuffer);
                    OpenGL4VertexArray(const OpenGL4VertexArray &other) = delete;
                    OpenGL4VertexArray(OpenGL4VertexArray &&other) noexcept;
                    virtual ~OpenGL4VertexArray();

                    OpenGL4VertexArray &operator =(const OpenGL4VertexArray &other) = delete;
                    OpenGL4VertexArray &operator =(OpenGL4VertexArray &&other) noexcept;

                    virtual void bind();
                    virtual void unbind();

                    virtual BindType getBindType() const;
                    virtual std::uint32_t getBindSlot() const;

                    bool hasIndexBuffer() const;

                    const std::shared_ptr<Layout> &getLayout() const;
                    void setLayout(std::shared_ptr<Layout> layout);

                private:
                    void reset(bool deleteNeeded);

                    GLuint handle;
                    Reference<OpenGL4Buffer> vertexBuffer;
                    Reference<OpenGL4Buffer> indexBuffer;
                    std::shared_ptr<Layout> layout;
            };
        }
    }
}

#endif // OPENGL4VERTEXARRAY_H
