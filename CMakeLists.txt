cmake_minimum_required(VERSION 3.9)

project ("Meshfab")

#modules
add_subdirectory(src/texturing)
add_subdirectory(src/modelload)
add_subdirectory(src/geometry)
add_subdirectory(src/renderer)

#excutable
add_subdirectory(src/qt-viewer)