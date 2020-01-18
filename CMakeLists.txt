cmake_minimum_required(VERSION 3.9)

project ("Meshfab")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_BUILD_RPATH "$ORIGIN")

#module
add_subdirectory(src/geometry)
add_subdirectory(src/renderer)

#excutable
add_subdirectory(src/client)