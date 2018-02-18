find_package(Eigen3 REQUIRED)

if(WIN32 OR UNIX AND NOT ANDROID)
    find_package(OpenCOLLADA)
    find_package(JPEG)
    find_package(PNG)
    find_package(TIFF)
    find_package(Boost COMPONENTS system filesystem REQUIRED)

    include_directories(SYSTEM ${OPENCOLLADA_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIRS})
endif(WIN32 OR UNIX AND NOT ANDROID)

if(WIN32)
    find_package(DirectX)
    find_package(OpenGL)
elseif(ANDROID)
    find_package(OpenGLES2)
elseif(UNIX AND NOT ANDROID)
    find_package(OpenGL)
endif(WIN32)

include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/${SOURCE_MAIN_CPP_DIR}" "${PROJECT_BINARY_DIR}/${SOURCE_MAIN_CPP_DIR}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Utilities/Config.h)

add_subdirectory(Core)
add_subdirectory(IO)
add_subdirectory(Math)
add_subdirectory(Physics)
add_subdirectory(Rendering)
add_subdirectory(Utilities)

set(INCLUDED_OBJECTS Core IO Rendering RenderingBackends Utilities)

if(OPENGL_FOUND)
    set(INCLUDED_OBJECTS ${INCLUDED_OBJECTS} OpenGL4)
endif(OPENGL_FOUND)

if(OPENGLES2_FOUND)
    set(INCLUDED_OBJECTS ${INCLUDED_OBJECTS} OpenGLES2)
endif(OPENGLES2_FOUND)

create_module(NAME ${PROJECT_NAME} PACKAGE AmberEngine COMPILATION_UNIT SHARED_LIBRARY OBJECTS ${INCLUDED_OBJECTS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${OPENCOLLADA_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/Amber FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.txx")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Utilities/Config.h DESTINATION include/Amber/Utilities)
