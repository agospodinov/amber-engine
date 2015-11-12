set(OPENGL4_SOURCES
    OpenGL4Renderer.cpp             OpenGL4Renderer.h
    OpenGL4Context.cpp              OpenGL4Context.h
    OpenGL4Object.cpp               OpenGL4Object.h
    OpenGL4Buffer.cpp               OpenGL4Buffer.h
    OpenGL4Framebuffer.cpp          OpenGL4Framebuffer.h
    OpenGL4VertexArray.cpp          OpenGL4VertexArray.h
    OpenGL4Program.cpp              OpenGL4Program.h
    OpenGL4Shader.cpp               OpenGL4Shader.h
    OpenGL4Texture.cpp              OpenGL4Texture.h
)

set(OPENGL4_GLSL_SOURCES
    GLSL/BaseModel.vsh              GLSL/BaseModel.fsh
    GLSL/Skybox.vsh                 GLSL/Skybox.fsh
)

add_definitions("-DCOMPILING_DLL")
# FIXME this flag should be removed
add_definitions("-DGL_GLEXT_PROTOTYPES")

add_library(OpenGL4 OBJECT ${OPENGL4_SOURCES})
add_custom_target(OpenGL4Shaders SOURCES ${OPENGL4_GLSL_SOURCES})
set_target_properties(OpenGL4 PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

install(DIRECTORY GLSL DESTINATION assets/graphics/shaders)
