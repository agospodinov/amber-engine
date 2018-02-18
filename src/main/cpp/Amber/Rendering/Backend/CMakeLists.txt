set(RENDERING_BACKENDS_LIB_SOURCES
    Layout.cpp          Layout.h
    Reference.txx       Reference.h
    BindLock.cpp        BindLock.h

    IRenderer.cpp       IRenderer.h
    IObject.cpp         IObject.h
    IContext.cpp        IContext.h
    IBindable.cpp       IBindable.h
    IMultiBindable.cpp  IMultiBindable.h
    IBuffer.cpp         IBuffer.h
    IRenderTarget.cpp   IRenderTarget.h
    IShader.cpp         IShader.h
    IProgram.cpp        IProgram.h
    ITexture.cpp        ITexture.h

    VertexTypes.cpp     VertexTypes.h
)

add_definitions("-DCOMPILING_DLL")

if(OPENGL_FOUND)
    add_subdirectory(OpenGL4)
endif(OPENGL_FOUND)

if(OPENGLES2_FOUND)
    add_subdirectory(OpenGLES2)
endif(OPENGLES2_FOUND)

add_library(RenderingBackends OBJECT ${RENDERING_BACKENDS_LIB_SOURCES})
set_target_properties(RenderingBackends PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")
