cmake_minimum_required(VERSION 3.15)
project(whatever)

set(SOURCES src/main.cpp src/shader.cpp src/ImageConverter.cpp src/glad.c)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE glfw OpenGL::GL)
