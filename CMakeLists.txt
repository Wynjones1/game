cmake_minimum_required(VERSION 2.8)
project(game)

include_directories("./deps/include")
file(GLOB SRC "./src/*.h" "./src/*.cpp")

add_executable(game ${SRC})

if(MSVC)
	include_directories("./deps/GLEW/include")
	include_directories("./deps/SDL2/include")
	include_directories("./deps/glm/include")

	target_link_libraries(game "./deps/GLEW/lib/Release/Win32/glew32s")
	target_link_libraries(game "./deps/SDL2/lib/x86/SDL2main")
	target_link_libraries(game "./deps/SDL2/lib/x86/SDL2")

	add_definitions("/wd4996")
	add_definitions(/DGLEW_STATIC)
else()
	include(FindPkgConfig)

	pkg_search_module(SDL2 REQUIRED sdl2)
	include_directories(${SDL2_INCLUDE_DIRS})
	target_link_libraries(game ${SDL2_LIBRARIES})

	find_package(GLEW)
	target_link_libraries(game ${GLEW_LIBRARIES})

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

find_package(OpenGL)
target_link_libraries(game ${OPENGL_LIBRARIES})

#add_definitions(-DGLM_FORCE_RADIANS)
