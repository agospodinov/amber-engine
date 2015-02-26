find_package(Eigen3 REQUIRED)

if(WIN32 OR UNIX AND NOT ANDROID)
    find_package(OpenCOLLADA)
    find_package(JPEG)
    find_package(PNG)
    find_package(TIFF)
endif(WIN32 OR UNIX AND NOT ANDROID)

if(WIN32)
    find_package(DirectX)
    find_package(OpenGL)
elseif(ANDROID)
    find_package(OpenGLES2)
elseif(UNIX AND NOT ANDROID)
    find_package(OpenGL)
endif(WIN32)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions("-std=c++11")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Utilities/Config.h)

add_subdirectory(Core)
add_subdirectory(IO)
add_subdirectory(Physics)
add_subdirectory(Rendering)
add_subdirectory(Utilities)

set(INCLUDED_OBJECTS $<TARGET_OBJECTS:Core> $<TARGET_OBJECTS:Rendering> $<TARGET_OBJECTS:Utilities>)

#if(OPENGL_FOUND)
#    set(INCLUDED_OBJECTS "${INCLUDED_OBJECTS} $<TARGET_OBJECTS:OpenGL4>")
#endif(OPENGL_FOUND)

add_library(${PROJECT_NAME} SHARED ${INCLUDED_OBJECTS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${OPENCOLLADA_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

install(TARGETS ${PROJECT_NAME} DESTINATION "${PLATFORM_INSTALL_DIR}/${CMAKE_BUILD_TYPE}")
