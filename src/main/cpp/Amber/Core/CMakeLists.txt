set(CORE_LIB_SOURCES
    Game.cpp            Game.h
    Player.cpp          Player.h
    Round.cpp           Round.h
    Scene.cpp           Scene.h

    ISystem.cpp         ISystem.h
)

#include_directories()
#link_directories()

add_library(Core OBJECT ${CORE_LIB_SOURCES})
set_target_properties(Core PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

#target_link_libraries(Core ...)
