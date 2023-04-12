cmake_minimum_required(VERSION 3.4)
include(ExternalProject)

project(RodeoKit
	LANGUAGES C CXX
	)

add_library(${PROJECT_NAME}
	"src/rodeo.c"
	"src/rodeo_math.c"
	"src/rodeo_string.c"
	"src/rodeo_log.c"
	"src/rodeo_input.c"
)

set_property(TARGET RodeoKit PROPERTY C_STANDARD 11)
set_property(TARGET RodeoKit PROPERTY CXX_STANDARD 11)

# pull all git submodules recursively
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

if(DEFINED EMSCRIPTEN)
	add_compile_definitions("__EMSCRIPTEN__")

	option(CGLM_SHARED "Shared build" OFF)
	option(CGLM_STATIC "Static build" ON)
	add_subdirectory(external/cglm)
	  
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
	ExternalProject_Get_Property(project_bgfx BINARY_DIR)
	add_library(bgfx STATIC IMPORTED)
	set_target_properties(bgfx PROPERTIES IMPORTED_LOCATION "${BINARY_DIR}/.build/wasm/bin/bgfxRelease.bc")
	add_dependencies(bgfx project_bgfx)

	add_library(bx STATIC IMPORTED)
	set_target_properties(bx PROPERTIES IMPORTED_LOCATION "${BINARY_DIR}/.build/wasm/bin/bxRelease.bc")
	add_dependencies(bx project_bgfx)

	add_library(bimg STATIC IMPORTED)
	set_target_properties(bimg PROPERTIES IMPORTED_LOCATION "${BINARY_DIR}/.build/wasm/bin/bimgRelease.bc")
	add_dependencies(bimg project_bgfx)

	target_include_directories(${PROJECT_NAME}
		PRIVATE external/bgfx/include
		PRIVATE external/bx/include
		PRIVATE external/cglm/include
		PRIVATE external/STC/include
		PRIVATE src
		PUBLIC include
		)
	target_link_directories(${PROJECT_NAME}
		PRIVATE external/bgfx
		)
	target_link_options(${PROJECT_NAME}
		PUBLIC "-lSDL"
		PUBLIC "-sMAX_WEBGL_VERSION=2"
		PUBLIC "-sMIN_WEBGL_VERSION=2"
		PUBLIC "-sWASM=1"
		PUBLIC "-sNO_EXIT_RUNTIME=1"
		PUBLIC "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1"
		PUBLIC "-sOFFSCREENCANVAS_SUPPORT=1"
		PUBLIC "-sALLOW_MEMORY_GROWTH=1"
		PUBLIC "-sUSE_SDL=2"
		PUBLIC "-sUSE_SDL_IMAGE=2"
		PUBLIC "-sSDL2_IMAGE_FORMATS='[\"png\"]'"
		)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		PRIVATE cglm
		PRIVATE bimg
		PRIVATE bgfx
		PRIVATE bx
		)
	target_compile_options(${PROJECT_NAME}
		PUBLIC "-fno-exceptions"
		PUBLIC "-fno-rtti"
		)
elseif(DEFINED UNIX AND NOT DEFINED APPLE)
	option(CGLM_SHARED "Shared build" OFF)
	option(CGLM_STATIC "Static build" ON)
	add_subdirectory(external/cglm)

	add_subdirectory(external/SDL)
	add_subdirectory(external/SDL_image)

	target_compile_options(${PROJECT_NAME}
		PRIVATE -Wall
		PRIVATE -Wextra
		PRIVATE -Wpedantic
		#PRIVATE -Werror
		PRIVATE -Wconversion
	)

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
	ExternalProject_Get_Property(project_bgfx BINARY_DIR)
	add_library(bgfx STATIC IMPORTED)
	set_target_properties(bgfx PROPERTIES IMPORTED_LOCATION "${BINARY_DIR}/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so")
	add_dependencies(bgfx project_bgfx)

	target_include_directories(${PROJECT_NAME}
		PRIVATE external/SDL/include
		PRIVATE external/SDL_image/include
		PRIVATE external/bgfx/include
		PRIVATE external/bx/include
		PRIVATE external/cglm/include
		PRIVATE external/STC/include
		PRIVATE src
		PUBLIC include
		)

	target_link_directories(${PROJECT_NAME}
		PRIVATE external/SDL
		PRIVATE external/SDL_image
		PRIVATE external/bgfx
		)
	target_link_libraries(${PROJECT_NAME}
		#PRIVATE SDL2::SDL2-static # static lib
		#PRIVATE SDL2::SDL2main
		PRIVATE SDL2::SDL2 # dynamic lib
		PRIVATE SDL2_image
		PRIVATE cglm
		PRIVATE bgfx
		)
endif()

add_dependencies(RodeoKit project_bgfx)
 
# build shaders
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND make --makefile=buildShaders.mk
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
) 
 
