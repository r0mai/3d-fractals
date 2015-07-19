cmake_minimum_required(VERSION 2.6)
project(3d-fractals)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

add_subdirectory(3rd)

include_directories(
    3rd/glfw-3.0.3/include/
    3rd/glm-0.9.4.0/
    3rd/glew-1.9.0/include/
)
