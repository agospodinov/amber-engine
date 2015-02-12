project(Amber)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
enable_testing()

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_definitions("-std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/vendor/include")

if(WIN32)
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/win32")
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/lib/win32/" DESTINATION "lib" FILES_MATCHING PATTERN "*.dll")
elseif(UNIX AND NOT ANDROID)
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/linux")
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/lib/linux/" DESTINATION "lib" FILES_MATCHING PATTERN "*.so*")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
elseif(ANDROID)
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/android")
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/lib/android/" DESTINATION "lib" FILES_MATCHING PATTERN "*.so*")
elseif(APPLE)
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/macosx")
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/lib/macosx/" DESTINATION "lib" FILES_MATCHING PATTERN "*.dylib")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

add_subdirectory(src)
add_subdirectory(test)

