set(UTILITIES_LIB_SOURCES
    ScopedDataPointer.cpp   ScopedDataPointer.h
    Logger.cpp              Logger.h

    Config.h.in
    Defines.h
)

#include_directories()
#link_directories()
add_definitions("-std=c++11")

add_library(Utilities OBJECT ${UTILITIES_LIB_SOURCES})
set_target_properties(Utilities PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

#target_link_libraries(Utilities ...)
