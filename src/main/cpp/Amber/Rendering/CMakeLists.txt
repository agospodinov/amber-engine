set(RENDERING_LIB_SOURCES
    Camera.cpp          Camera.h
    Mesh.cpp            Mesh.h
    Material.cpp        Material.h
    Light.cpp           Light.h
    Scene.cpp           Scene.h

    Viewport.cpp        Viewport.h
    RenderingSystem.cpp RenderingSystem.h

    IRenderingStrategy.cpp  IRenderingStrategy.h

    ForwardDeclarations.h
)

add_definitions("-DCOMPILING_DLL")

add_subdirectory(Backend)

add_library(Rendering OBJECT ${RENDERING_LIB_SOURCES})
set_target_properties(Rendering PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")
