cmake_minimum_required(VERSION 3.25.1)
include(ExternalProject)

project(RodeoEngine)

file(GLOB SOURCES
	"src/rodeo.c"
	)

#add_library(lib src/lib.c)

add_library(${PROJECT_NAME} ${SOURCES})

add_subdirectory(external/SDL)

ExternalProject_Add(project_bgfx
	#BUILD_IN_SOURCE true # this just doesn't work
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx"
	BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx"
	DOWNLOAD_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND make linux
	INSTALL_COMMAND ""
	)


target_include_directories(${PROJECT_NAME}
	PUBLIC external/SDL/include
	PUBLIC external/bgfx/include
	PUBLIC external/bx/include
	PUBLIC include
	)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/SDL
	PRIVATE external/bgfx
	)

ExternalProject_Get_Property(project_bgfx BINARY_DIR)
#message("++" ${BINARY_DIR})
target_link_libraries(${PROJECT_NAME}
	SDL2::SDL2 # dynamic lib
	#SDL3::SDL3 # dynamic lib
	#SDL3::SDL3-static # static lib
	${BINARY_DIR}/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so
	)
