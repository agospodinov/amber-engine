project(Amber)
cmake_minimum_required(VERSION 3.1)

include(cmake/Utils.cmake)
enable_testing()

add_subdirectory(src/main/cpp)
add_subdirectory(src/main/java)
add_subdirectory(src/test)
add_subdirectory(src/tools)

create_exports(PACKAGE AmberEngine VERSION 0.1 LIBRARIES Amber)
