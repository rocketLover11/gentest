cmake_minimum_required(VERSION 3.16)

project(gentest C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(gentest
    src/main.c
)

target_link_libraries(gentest
    glfw
    OpenGL::GL
)