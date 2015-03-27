set(RENDERING_LIB_SOURCES
    Camera.cpp          Camera.h
    Scene.cpp           Scene.h
    Model.cpp           Model.h
    Mesh.cpp            Mesh.h
    Material.cpp        Material.h
    Light.cpp           Light.h
    Layout.cpp          Layout.h
    Skybox.cpp          Skybox.h

    Reference.txx       Reference.h
    BindLock.cpp        BindLock.h
    Node.cpp            Node.h
    Procedure.cpp       Procedure.h
    RenderStage.cpp     RenderStage.h
    ShaderPass.cpp      ShaderPass.h
    Viewport.cpp        Viewport.h

    IRenderer.cpp       IRenderer.h
    IRenderable.cpp     IRenderable.h
    IObject.cpp         IObject.h
    IContext.cpp        IContext.h
    IBindable.cpp       IBindable.h
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

add_library(Rendering OBJECT ${RENDERING_LIB_SOURCES})
set_target_properties(Rendering PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")
