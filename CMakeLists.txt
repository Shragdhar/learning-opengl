cmake_minimum_required(VERSION 3.15)
project(whatever)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(main main.cpp glad.c)
target_link_libraries(main PRIVATE glfw OpenGL::GL)