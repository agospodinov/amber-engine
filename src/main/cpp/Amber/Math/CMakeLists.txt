set(MATH_LIB_SOURCES
    Utilities.h
)

add_definitions("-DCOMPILING_DLL")

add_library(Math OBJECT ${MATH_LIB_SOURCES})
set_target_properties(Math PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

