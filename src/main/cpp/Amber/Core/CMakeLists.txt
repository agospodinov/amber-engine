set(CORE_LIB_SOURCES
    Game.cpp            Game.h
    Player.cpp          Player.h
    Round.cpp           Round.h
    World.cpp           World.h
    Entity.cpp          Entity.h
    Transform.cpp       Transform.h

    ISystem.cpp         ISystem.h
    IComponent.cpp      IComponent.h
)

#include_directories()
#link_directories()

add_library(Core OBJECT ${CORE_LIB_SOURCES})
set_target_properties(Core PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

#target_link_libraries(Core ...)
