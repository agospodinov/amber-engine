set(PHYSICS_LIB_SOURCES
    AmberModelLoader.cpp        AmberModelLoader.h
    ColladaModelLoader.cpp      ColladaModelLoader.h
    MeshBuilder.cpp             MeshBuilder.h
    ShaderLoader.cpp            ShaderLoader.h
    ImageTextureLoader.cpp      ImageTextureLoader.h
    AssetManager.cpp            AssetManager.h

    IModelLoader.cpp            IModelLoader.h
    ITextureLoader.cpp          ITextureLoader.h
)

#include_directories()
#link_directories()

add_library(IO OBJECT ${PHYSICS_LIB_SOURCES})
set_target_properties(IO PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

#target_link_libraries(Core ...)
