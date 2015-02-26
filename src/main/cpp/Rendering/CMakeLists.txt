set(RENDERING_LIB_SOURCES
    IRenderer.cpp   IRenderer.h
)

#include_directories()
#link_directories()
add_definitions("-std=c++11")

add_library(Rendering OBJECT ${RENDERING_LIB_SOURCES})
set_target_properties(Rendering PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

#target_link_libraries(Rendering ...)
