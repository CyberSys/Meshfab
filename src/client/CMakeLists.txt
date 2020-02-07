cmake_minimum_required(VERSION 3.9)

project ("client-Viewer")

# list the header files
set(HEADER_FILES
)

# list the source files
set(SOURCE_FILES
	src/main.cpp
	
	src/App.h
	src/App.cpp
	src/Input.h
	src/Input.cpp
	
	src/UI.h
	src/UI.cpp
	src/Actions.h
	src/Actions.cpp
	src/imgui/imconfig.h
	src/imgui/imgui.h
	src/imgui/imgui.cpp
	src/imgui/imgui_draw.cpp
	src/imgui/imgui_impl_glfw.h
	src/imgui/imgui_impl_glfw.cpp
	src/imgui/imgui_impl_opengl3.h
	src/imgui/imgui_impl_opengl3.cpp
	src/imgui/imgui_internal.h
	src/imgui/imgui_widgets.cpp
	src/imgui/ImGuiFileDialog.h
	src/imgui/ImGuiFileDialog.cpp
)

# add library target
add_executable(client-Viewer
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(client-Viewer
	PUBLIC
		opengl32
		glew32
		glfw3
		
		#system modules.
		Renderer
		Geometry
		Texturing
)


if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

	add_custom_command(
    TARGET client-Viewer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/x64/glew32.dll
	$<TARGET_FILE_DIR:client-Viewer>
)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
add_custom_command(
    TARGET client-Viewer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/Win32/glew32.dll
	$<TARGET_FILE_DIR:client-Viewer>
)

ENDIF()


if(WIN32)
	target_compile_definitions(client-Viewer
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(client-Viewer
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(client-Viewer PUBLIC cxx_std_17)
set_target_properties(client-Viewer PROPERTIES
	CXX_EXTENSIONS OFF
)

# list include directories
target_include_directories(client-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm
	
	#system modules includes
	${Renderer_INCLUDE_DIRS}/
	${Geometry_INCLUDE_DIRS}/
	${Texturing_INCLUDE_DIRS}/
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (client-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/x64lib/
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (client-Viewer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/win32lib/
)
ENDIF()
