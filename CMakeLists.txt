cmake_minimum_required(VERSION 3.25.1)
include(ExternalProject)

project(RodeoEngine)

set(CMAKE_BUILD_TYPE Debug)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -std=c++11")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s MIN_WEBGL_VERSION=2")
endif()
option(CGLM_SHARED "Shared build" OFF)
option(CGLM_STATIC "Static build" ON)

file(GLOB SOURCES
	"src/rodeo.c"
	"src/rodeo_math.c"
	"src/rodeo_types.c"
	"src/rodeo_string.c"
	"src/rodeo_log.c"
	"src/rodeo_input.c"
	)

#add_library(lib src/lib.c)

add_library(${PROJECT_NAME} ${SOURCES})

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
target_compile_options(${PROJECT_NAME} PRIVATE
-Wall
-Wextra
-Wpedantic
#-Werror
-Wconversion
)
endif()

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


if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	add_subdirectory(external/SDL)
	add_subdirectory(external/SDL_image)
endif()
add_subdirectory(external/cglm)

message("this is the dir")
message(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND make --makefile=buildShaders.mk
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	ExternalProject_Add(project_bgfx
		#BUILD_IN_SOURCE true # this just doesn't work
		SOURCE_DIR "external/bgfx"
		BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx"
		DOWNLOAD_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND make wasm-release
		INSTALL_COMMAND ""
		BUILD_ALWAYS TRUE
		)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	ExternalProject_Add(project_bgfx
		#BUILD_IN_SOURCE true # this just doesn't work
		SOURCE_DIR "external/bgfx"
		BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx"
		DOWNLOAD_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND make linux-release64
		INSTALL_COMMAND ""
		BUILD_ALWAYS TRUE
		)
endif()

add_dependencies(RodeoEngine project_bgfx)


if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	target_include_directories(${PROJECT_NAME}
		PUBLIC external/bgfx/include
		PUBLIC external/bx/include
		PUBLIC external/cglm/include
		PUBLIC external/STC/include
		PUBLIC include
		PRIVATE src
		)

	target_link_directories(${PROJECT_NAME}
		PRIVATE external/bgfx
		)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_include_directories(${PROJECT_NAME}
		PUBLIC external/SDL/include
		PUBLIC external/SDL_image/include
		PUBLIC external/bgfx/include
		PUBLIC external/bx/include
		PUBLIC external/cglm/include
		PUBLIC external/STC/include
		PUBLIC include
		PRIVATE src
		)

	target_link_directories(${PROJECT_NAME}
		PRIVATE external/SDL
		PRIVATE external/SDL_image
		PRIVATE external/bgfx
		)
endif()

ExternalProject_Get_Property(project_bgfx BINARY_DIR)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	target_link_libraries(${PROJECT_NAME} PRIVATE
		cglm
		${BINARY_DIR}/.build/wasm/bin/bgfxRelease.bc
		${BINARY_DIR}/.build/wasm/bin/bxRelease.bc
		${BINARY_DIR}/.build/wasm/bin/bimgRelease.bc
		)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PRIVATE
		#SDL2::SDL2-static # static lib
		#SDL2::SDL2main
		SDL2::SDL2 # dynamic lib
		SDL2_image
		cglm
		${BINARY_DIR}/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so
		)
endif()
