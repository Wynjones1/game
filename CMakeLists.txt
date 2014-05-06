cmake_minimum_required(VERSION 2.8)
project(game)

include(FindPkgConfig)



include_directories("./deps/include")
file(GLOB SRC "./src/*.h" "./src/*.cpp")

add_executable(game ${SRC})

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(game ${SDL2_LIBRARIES})

target_link_libraries(game ${GLEW_LIBRARIES})

find_package(OpenGL)
target_link_libraries(game ${OPENGL_LIBRARIES})

find_package(GLEW)
target_link_libraries(game ${GLEW_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-DGLM_FORCE_RADIANS)
