cmake_minimum_required(VERSION 3.15)
project(main)

# For debugging
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(source_dir src)

file(GLOB_RECURSE sources ${source_dir}/*.cpp ${source_dir}/*.c ${source_dir}/*.h)

add_executable(main ${sources})

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Enable for SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(main ${SDL2_LIBRARIES})

# Enable for OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)
