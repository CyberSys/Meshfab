cmake_minimum_required(VERSION 3.9)

project ("ModelLoad")

# list the header files
set(HEADER_FILES
)

# list the source files
set(SOURCE_FILES

	src/Model.h
	src/Model.cpp
)

# add library target
add_library(ModelLoad
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(ModelLoad
	PUBLIC
		opengl32
		glew32
		assimp-vc141-mt

		#system modules.
		Texturing
)

# copy assimp dll to exe folder
#if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
#
#add_custom_command(
#    TARGET ModelLoad POST_BUILD
#		
#	COMMAND ${CMAKE_COMMAND} -E copy 
#	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/x64/assimp-vc141-mt.dll
#	 $<TARGET_FILE_DIR:QT-VIEWER>
#)
#else("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
#add_custom_command(
#    TARGET ModelLoad POST_BUILD
#		
#	COMMAND ${CMAKE_COMMAND} -E copy 
#	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/Win32/assimp-vc141-mt.dll
#	 $<TARGET_FILE_DIR:QT-VIEWER>
#)
#ENDIF()

if(WIN32)
	target_compile_definitions(ModelLoad
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(ModelLoad
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(ModelLoad PUBLIC cxx_std_17)
set_target_properties(ModelLoad PROPERTIES
	CXX_EXTENSIONS OFF
)


# list include directories
target_include_directories(ModelLoad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm

	#system modules includes
	${Texturing_INCLUDE_DIRS}/
)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_include_directories (ModelLoad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/x64/include
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_include_directories (ModelLoad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/Win32/include
)
ENDIF()

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (ModelLoad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/x64
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (ModelLoad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
	${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/Win32
)
ENDIF()

# Expose Renderer's public includes (including the ones of ModelLoad's dependencies
# transitively) to other subprojects through cache variable.
set(ModelLoad_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                                 ${ModelLoad_INCLUDE_DIRS}
    CACHE INTERNAL "ModelLoad: Include Directories" FORCE)
