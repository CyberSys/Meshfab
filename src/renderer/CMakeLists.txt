cmake_minimum_required(VERSION 3.9)

project ("Renderer")

# list the header files
set(HEADER_FILES
)

# list the source files
set(SOURCE_FILES
	src/Materials/Materials.h
	src/Materials/Materials.cpp
	src/Materials/Private/ShaderProgram.h
	src/Materials/Private/ShaderProgram.cpp
	src/Materials/Private/DefaultMaterial.h
	src/Materials/Private/DefaultMaterial.cpp
	src/Materials/Private/PhongMaterial.h
	src/Materials/Private/PhongMaterial.cpp
	src/Materials/Private/DiffuseMaterial.h
	src/Materials/Private/DiffuseMaterial.cpp
	src/Materials/Private/CheckboardMaterial.h
	src/Materials/Private/CheckboardMaterial.cpp
	src/Materials/Private/ColoredMaterial.h
	src/Materials/Private/ColoredMaterial.cpp
	src/Materials/Private/FramerenderMaterial.h
	src/Materials/Private/FramerenderMaterial.cpp
	
	src/Scene.h
	src/Scene.cpp
	src/SceneObject.h
	src/SceneObject.cpp
	src/camera.h
	src/camera.cpp
	src/FrameBuffer.h
	src/FrameBuffer.cpp
	src/Framerenderer.h
	src/Framerenderer.cpp
	src/Transform.h
	src/Transform.cpp
	src/renderer.h
	src/renderer.cpp
)

# add library target
add_library(Renderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(Renderer
	PUBLIC
		opengl32
		glew32
		
		#system modules.
		Geometry
)

if(WIN32)
	target_compile_definitions(Renderer
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(Renderer
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(Renderer PUBLIC cxx_std_17)
set_target_properties(Renderer PROPERTIES
	CXX_EXTENSIONS OFF
)

# list include directories
target_include_directories(Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm
	
	#system modules includes
	${Geometry_INCLUDE_DIRS}/
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
)
ENDIF()

# Expose Renderer's public includes (including the ones of Geometry's dependencies
# transitively) to other subprojects through cache variable.
set(Renderer_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                                 ${Renderer_INCLUDE_DIRS}
    CACHE INTERNAL "Renderer: Include Directories" FORCE)