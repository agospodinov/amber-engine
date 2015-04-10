#include "OpenGL4Object.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Object::OpenGL4Object()
                : handle(0)
            {
            }

            OpenGL4Object::OpenGL4Object(GLuint handle)
                : handle(handle)
            {
            }

            OpenGL4Object::~OpenGL4Object()
            {
                handle = 0;
            }

            GLuint OpenGL4Object::getHandle() const
            {
                return handle;
            }
        }
    }
}
