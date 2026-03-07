#include <GLFW/glfw3.h>
#include <stdio.h>
#include "renderer/renderer.h"
#include "tilemap.h"

#define TILE_SIZE 16
#define MAP_W 10
#define MAP_H 10

int main() {
    printf("Starting gentest...");

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "gentest", NULL, NULL);

    if (!window) {
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int map[MAP_W*MAP_H] = {
        0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,
        3,3,3,3,3,3,3,3,3,3,
        4,4,4,4,4,4,4,4,4,4,
        0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,
        3,3,3,3,3,3,3,3,3,3,
        4,4,4,4,4,4,4,4,4,4,
    };

    unsigned int atlas = load_texture();

    glOrtho(0, MAP_W*TILE_SIZE, MAP_H*TILE_SIZE, 0, -1, 1);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_tilemap(atlas, map, MAP_W, MAP_H, TILE_SIZE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}