cmake_minimum_required(VERSION 3.21)
project(Raycasting C)

set(CMAKE_C_STANDARD 17)

add_compile_options(-Wall)

set(CMAKE_C_FLAGS "-fopenmp")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)

include_directories("vendor/glad/include")

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(Raycasting src/main.c src/file_reader.h src/file_reader.c vendor/glad/src/glad.c src/renderer.c src/renderer.h src/util.h src/window.c src/window.h src/color.c src/color.h src/map.c src/map.h src/log.h src/shaders.c src/shaders.h src/raycaster.c src/raycaster.h src/player.c src/player.h src/color_hash_map.c src/color_hash_map.h)

target_link_libraries(Raycasting glfw)