#ifndef OPENGL4OBJECT_H
#define OPENGL4OBJECT_H

#include <GL/gl.h>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Object
            {
                public:
                    OpenGL4Object();
                    OpenGL4Object(const OpenGL4Object &other) = delete;
                    OpenGL4Object(OpenGL4Object &&other) noexcept;
                    virtual ~OpenGL4Object() = 0;

                    OpenGL4Object &operator =(const OpenGL4Object &other) = delete;
                    OpenGL4Object &operator =(OpenGL4Object &&other) noexcept;

                    virtual GLuint getHandle() const final;

                protected:
                    OpenGL4Object(GLuint handle);

                    GLuint handle;
            };
        }
    }
}

#endif // OPENGL4OBJECT_H
