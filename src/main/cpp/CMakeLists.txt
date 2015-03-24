find_package(Eigen3 REQUIRED)

if(WIN32 OR UNIX AND NOT ANDROID)
    find_package(OpenCOLLADA)
    find_package(JPEG)
    find_package(PNG)
    find_package(TIFF)

    include_directories(SYSTEM ${OPENCOLLADA_INCLUDE_DIRS})
endif(WIN32 OR UNIX AND NOT ANDROID)

if(WIN32)
    find_package(DirectX)
    find_package(OpenGL)
elseif(ANDROID)
    find_package(OpenGLES2)
elseif(UNIX AND NOT ANDROID)
    find_package(OpenGL)
endif(WIN32)

include_directories(${EIGEN3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions("-std=c++11")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Utilities/Config.h)

add_subdirectory(Core)
add_subdirectory(IO)
add_subdirectory(Math)
add_subdirectory(Physics)
add_subdirectory(Rendering)
add_subdirectory(Utilities)

set(INCLUDED_OBJECTS $<TARGET_OBJECTS:Core> $<TARGET_OBJECTS:IO> $<TARGET_OBJECTS:Rendering> $<TARGET_OBJECTS:Utilities>)

if(OPENGL_FOUND)
    set(INCLUDED_OBJECTS ${INCLUDED_OBJECTS} $<TARGET_OBJECTS:OpenGL4>)
endif(OPENGL_FOUND)

if(OPENGLES2_FOUND)
    set(INCLUDED_OBJECTS ${INCLUDED_OBJECTS} $<TARGET_OBJECTS:OpenGLES2>)
endif(OPENGLES2_FOUND)

add_library(${PROJECT_NAME} SHARED ${INCLUDED_OBJECTS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${OPENCOLLADA_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL "COMPILING_DLL")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/Amber FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
if(WIN32)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib/win32)
elseif(UNIX AND NOT ANDROID)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib/linux)
elseif(ANDROID)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib/android)
elseif(APPLE)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib/macosx)
endif(WIN32)
