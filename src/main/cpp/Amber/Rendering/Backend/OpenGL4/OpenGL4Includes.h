#ifndef OPENGL4INCLUDES_H
#define OPENGL4INCLUDES_H

#if defined(__APPLE__)
# include <OpenGL/gl3.h>
# include <OpenGL/gl3ext.h>
#else
# if defined(_WIN32)
#  include <windows.h>
# endif
# include <GL/gl.h>
# include <GL/glext.h>
#endif

#endif
