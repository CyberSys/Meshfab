cmake_minimum_required(VERSION 3.9)

project ("Geometry")

# list the header files
set(HEADER_FILES
)

# list the source files
set(SOURCE_FILES
	src/Shape3D.h
	src/Shape3D.cpp
	src/Shape2D.h
	src/Shape2D.cpp
	
	src/private/Cube.h
	src/private/Cube.cpp
	src/private/BoundingBox.h
	src/private/BoundingBox.cpp
	src/private/Model3D.h
	src/private/Model3D.cpp
	src/private/Quad.h
	src/private/Quad.cpp
	src/private/Grid.h
	src/private/Grid.cpp
	src/private/GeomtryInfo.h
	src/private/halfedge/Halfedge.h
	src/private/halfedge/Halfedge.cpp
	src/private/halfedge/Face.h
	src/private/halfedge/Face.cpp
	src/private/halfedge/Vertex.h
	src/private/halfedge/Vertex.cpp
	src/private/halfedge/Mesh.h
	src/private/halfedge/Mesh.cpp
)

# add library target
add_library(Geometry
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(Geometry
	PUBLIC
		opengl32
		glew32

		#system modules.
		ModelLoad
)

if(WIN32)
	target_compile_definitions(Geometry
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(Geometry
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(Geometry PUBLIC cxx_std_17)
set_target_properties(Geometry PROPERTIES
	CXX_EXTENSIONS OFF
)


# list include directories
target_include_directories(Geometry
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm

	#system modules includes
	${ModelLoad_INCLUDE_DIRS}/
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (Geometry
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (Geometry
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
)
ENDIF()

# Expose Renderer's public includes (including the ones of Geometry's dependencies
# transitively) to other subprojects through cache variable.
set(Geometry_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                                 ${Geometry_INCLUDE_DIRS}
    CACHE INTERNAL "Geometry: Include Directories" FORCE)
