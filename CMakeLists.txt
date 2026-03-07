cmake_minimum_required(VERSION 3.16)

project(gentest C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(gentest ${SOURCES})

target_include_directories(gentest PRIVATE 
    include
    src/renderer
    src/tilemap
)

target_link_libraries(gentest
    glfw
    OpenGL::GL
    m
)