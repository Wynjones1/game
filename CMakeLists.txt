cmake_minimum_required(VERSION 2.8)
project(game)

file(GLOB BASE_SRC "./src/base/*.cpp" "./deps/gl3w/src/gl3w.c")
add_library(base ${BASE_SRC})

include_directories("./deps/SDL2/include")
include_directories("./deps/glm/include")
include_directories("./deps/gl3w/include")
include_directories("./src/base")

add_definitions(-DGLM_FORCE_RADIANS)

if(MSVC)
	target_link_libraries(base "./deps/SDL2/lib/x86/SDL2main")
	target_link_libraries(base "./deps/SDL2/lib/x86/SDL2")

	add_definitions("/wd4996")
else()
	include(FindPkgConfig)

	pkg_search_module(SDL2 REQUIRED sdl2)
	include_directories(${SDL2_INCLUDE_DIRS})
	target_link_libraries(base ${SDL2_LIBRARIES})

	target_link_libraries(base ${CMAKE_DL_LIBS})

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

find_package(OpenGL)
target_link_libraries(base ${OPENGL_LIBRARIES})

file(GLOB TESTING_SRC "./src/testing/*.h" "./src/testing/*.cpp" )
file(GLOB SRC "./src/*.h" "./src/*.cpp")

add_executable(game ${SRC})
add_executable(testing ${TESTING_SRC})

target_link_libraries(game base)
target_link_libraries(testing base)



