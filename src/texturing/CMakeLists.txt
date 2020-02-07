cmake_minimum_required(VERSION 3.9)

project ("Texturing")

# list the header files
set(HEADER_FILES
)

# list the source files
set(SOURCE_FILES
	src/Texture.h
	src/Texture.cpp
	
	src/stb/stb_image.h
	src/stb/stb_image.cpp
	src/stb/stb_image_aug.h
	src/stb/stb_image_aug.c
)

# add library target
add_library(Texturing
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(Texturing
	PUBLIC
		opengl32
		glew32
)

if(WIN32)
	target_compile_definitions(Texturing
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(Texturing
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(Texturing PUBLIC cxx_std_17)
set_target_properties(Texturing PROPERTIES
	CXX_EXTENSIONS OFF
)


# list include directories
target_include_directories(Texturing
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (Texturing
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (Texturing
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
)
ENDIF()

# Expose Texturing's public includes (including the ones of Geometry's dependencies
# transitively) to other subprojects through cache variable.
set(Texturing_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                                 ${Texturing_INCLUDE_DIRS}
    CACHE INTERNAL "Texturing: Include Directories" FORCE)