cmake_minimum_required(VERSION 2.6)
project(3d-fractals)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14")

add_subdirectory(3rd)

include_directories(SYSTEM 3rd/glfw-3.0.3/include/)
include_directories(SYSTEM 3rd/glm-0.9.4.0/)
include_directories(SYSTEM 3rd/glew-1.9.0/include/)
include_directories(src/)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLFW_303
    GLEW_190
)

add_subdirectory(shaders)
add_subdirectory(src)
add_subdirectory(bin)
