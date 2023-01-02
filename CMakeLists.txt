cmake_minimum_required(VERSION 3.25.1)

project(space_squad)

file(GLOB SOURCES
	"src/main.c"
	"src/lib/lib.c"
	)

#add_library(lib src/lib.c)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(external/SDL)

target_include_directories(${PROJECT_NAME}
	PUBLIC external/SDL/include
	)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/SDL
	)

target_link_libraries(${PROJECT_NAME}
	SDL2::SDL2 # dynamic lib
	#SDL3::SDL3 # dynamic lib
	#SDL3::SDL3-static # static lib
	)
