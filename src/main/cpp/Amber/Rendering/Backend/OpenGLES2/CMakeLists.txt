set(OPENGLES2_SOURCES
#    OpenGLRenderer.cpp              OpenGLRenderer.h
#    OpenGLContext.cpp               OpenGLContext.h
#    OpenGLBuffer.cpp                OpenGLBuffer.h
#    OpenGLFramebuffer.cpp           OpenGLFramebuffer.h
#    OpenGLVertexArray.cpp           OpenGLVertexArray.h
#    OpenGLProgram.cpp               OpenGLProgram.h
#    OpenGLShader.cpp                OpenGLShader.h
#    OpenGLTexture.cpp               OpenGLTexture.h
)

#set(OPENGLES2_GLSL_SOURCES
#    GLSL/Base.vsh                   GLSL/Base.fsh
#    GLSL/Skybox.vsh                 GLSL/Skybox.fsh
#)

add_definitions("-DCOMPILING_DLL")
add_definitions("-DGL_GLEXT_PROTOTYPES")

add_library(OpenGLES2 OBJECT ${OPENGLES2_SOURCES})
add_custom_target(OpenGLES2Shaders SOURCES ${OPENGLES2_GLSL_SOURCES})
set_target_properties(OpenGLES2 PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

install(DIRECTORY GLSL DESTINATION assets/graphics/shaders)
