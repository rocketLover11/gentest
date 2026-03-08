cmake_minimum_required(VERSION 3.16)

project(adventure_game C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(adventure_game ${SOURCES})
add_executable(world_test
    src/world/worldtest/generator.c
    src/world/worldtest/perlin/noise1234.c
)

target_include_directories(adventure_game PRIVATE 
    include
    src/renderer
    src/player
    src/tilemap
    src/world/worldtest/perlin
)

target_include_directories(world_test PRIVATE
    ${SDL2_INCLUDE_DIRS}
    src/world/worldtest/perlin
)

target_link_libraries(adventure_game
    glfw
    OpenGL::GL
    m
)

target_link_libraries(world_test
    ${SDL2_LIBRARIES}
    m
)

add_custom_command(TARGET adventure_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:adventure_game>
)