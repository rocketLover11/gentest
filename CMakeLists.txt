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
    src/player
    src/tilemap
)

target_link_libraries(gentest
    glfw
    OpenGL::GL
    m
)

add_custom_command(TARGET gentest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:gentest>
)