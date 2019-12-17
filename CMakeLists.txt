cmake_minimum_required(VERSION 3.9)

project ("Meshfab-Viewer")

# list the header files
set(HEADER_FILES

)

# list the source files
set(SOURCE_FILES
	src/main.cpp

	src/GeoShapes/Shape3D.h
	src/GeoShapes/Shape3D.cpp
	src/GeoShapes/Shape2D.h
	src/GeoShapes/Shape2D.cpp
	src/GeoShapes/private/cube.h
	src/GeoShapes/private/cube.cpp
	src/GeoShapes/private/Quad.h
	src/GeoShapes/private/Quad.cpp
	src/GeoShapes/private/GPUBufferID.h
	
	src/Materials/Materials.h
	src/Materials/Materials.cpp
	src/Materials/Private/ShaderProgram.h
	src/Materials/Private/ShaderProgram.cpp
	src/Materials/Private/ColoredMaterial.h
	src/Materials/Private/ColoredMaterial.cpp
	src/Materials/Private/FramerenderMaterial.h
	src/Materials/Private/FramerenderMaterial.cpp
	
	src/App.h
	src/App.cpp
	src/Scene3D.h
	src/Scene3D.cpp
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
)

# add library target
add_executable(MF-Viewer
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(MF-Viewer
	PUBLIC
		opengl32
		glew32
		glfw3
		#libfbxsdk-md.lib
		#libxml2-md.lib
		#zlib-md.lib
)


if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

	add_custom_command(
    TARGET MF-Viewer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/x64/glew32.dll
	$<TARGET_FILE_DIR:MF-Viewer>
)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
add_custom_command(
    TARGET MF-Viewer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/Win32/glew32.dll
	$<TARGET_FILE_DIR:MF-Viewer>
)

ENDIF()


if(WIN32)
	target_compile_definitions(MF-Viewer
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(MF-Viewer
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(MF-Viewer PUBLIC cxx_std_17)
set_target_properties(MF-Viewer PROPERTIES
	CXX_EXTENSIONS OFF
)


# list include directories
target_include_directories(MF-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer3D
	${CMAKE_CURRENT_SOURCE_DIR}/external/
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/FBX/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm
	${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image
	${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
	${CMAKE_CURRENT_SOURCE_DIR}/resources
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (MF-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/x64lib/
	${CMAKE_CURRENT_SOURCE_DIR}/external/FBX/lib/vs2017/x64/debug
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (MF-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/win32lib/
	${CMAKE_CURRENT_SOURCE_DIR}/external/FBX/lib/vs2017/x86/debug
)
ENDIF()
