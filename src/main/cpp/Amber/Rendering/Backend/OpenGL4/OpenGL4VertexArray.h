#ifndef OPENGL4VERTEXARRAY_H
#define OPENGL4VERTEXARRAY_H

#include "Amber/Rendering/Backend/IBindable.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Object.h"

#include "Amber/Rendering/Backend/Layout.h"
#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Includes.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Buffer;

            class OpenGL4VertexArray : public IBindable, public OpenGL4Object
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

                    const Layout &getLayout() const;
                    void setLayout(Layout layout);

                private:
                    void reset(bool deleteNeeded);
                    GLenum getGLComponentType(Layout::ComponentType type) const;

                    Reference<OpenGL4Buffer> vertexBuffer;
                    Reference<OpenGL4Buffer> indexBuffer;
                    Layout layout;
            };
        }
    }
}

#endif // OPENGL4VERTEXARRAY_H
