cmake_minimum_required(VERSION 3.25.1)
include(ExternalProject)

project(RodeoEngine)

file(GLOB SOURCES
	"src/rodeo.c"
	"src/rodeo_math.c"
	)

#add_library(lib src/lib.c)

add_library(${PROJECT_NAME} ${SOURCES})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if(GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

add_subdirectory(external/SDL)
add_subdirectory(external/cglm EXCLUDE_FROM_ALL)

ExternalProject_Add(project_bgfx
	#BUILD_IN_SOURCE true # this just doesn't work
	SOURCE_DIR "external/bgfx"
	BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx"
	DOWNLOAD_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND make linux
	INSTALL_COMMAND ""
	)

add_dependencies(RodeoEngine project_bgfx)


target_include_directories(${PROJECT_NAME}
	PUBLIC external/SDL/include
	PUBLIC external/bgfx/include
	PUBLIC external/bx/include
	PUBLIC external/cglm/include
	PUBLIC include
	)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/SDL
	PRIVATE external/bgfx
	)


ExternalProject_Get_Property(project_bgfx BINARY_DIR)
#message("++" ${BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL2::SDL2 # dynamic lib
	cglm_headers
	${BINARY_DIR}/.build/linux64_gcc/bin/libbgfx-shared-libDebug.so
	)
