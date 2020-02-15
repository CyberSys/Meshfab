cmake_minimum_required(VERSION 3.9)

project ("QT-VIEWER")

# list the header files
set(HEADER_FILES
	src/Window.h
	src/App.h
)

# list the source files
set(SOURCE_FILES
	src/main.cpp
	src/Window.cpp
	src/App.cpp
)

# link with qt5
find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)
qt5_wrap_cpp(HEADER_MOC ${HEADER_FILES})

# add library target
add_executable(QT-VIEWER
	${HEADER_FILES}
	${SOURCE_FILES}
	${HEADER_MOC}
	${RCC_SOURCES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UI_FILES})

set(QT_LIBS
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
	Qt5::Widgets
)

target_link_libraries(QT-VIEWER
	PUBLIC
		${QT_LIBS}
		opengl32
		glew32
)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

add_custom_command(
    TARGET QT-VIEWER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
		$<TARGET_FILE:Qt5::Core>
		$<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:QT-VIEWER>
		
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/x64/glew32.dll
	 $<TARGET_FILE_DIR:QT-VIEWER>
)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
add_custom_command(
    TARGET QT-VIEWER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
		$<TARGET_FILE:Qt5::Core>
		$<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:QT-VIEWER>
		
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/Win32/glew32.dll
	 $<TARGET_FILE_DIR:QT-VIEWER>
)
ENDIF()

# copy resources folder to exe folder
add_custom_command(
    TARGET QT-VIEWER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:QT-VIEWER>/resources
)
# copy resources folder to .sln folder
add_custom_command(
    TARGET QT-VIEWER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/resources ${PROJECT_BINARY_DIR}/resources
)

# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(QT-VIEWER
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(QT-VIEWER
		PRIVATE
			/WX
	)
endif()

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(QT-VIEWER PUBLIC cxx_std_17)
set_target_properties(QT-VIEWER PROPERTIES
	CXX_EXTENSIONS OFF
)

# define debug macro
target_compile_definitions(QT-VIEWER PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")


# list include directories
target_include_directories(QT-VIEWER
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (QT-VIEWER
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (QT-VIEWER
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
)
ENDIF()