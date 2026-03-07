#include <GLFW/glfw3.h>
#include <stdio.h>

#include "renderer/renderer.h"
#include "player/player.h"
#include "tilemap.h"

#define TILE_SIZE 16
#define PLAYER_WIDTH 2
#define PLAYER_HEIGHT 5
#define MAP_W 10
#define MAP_H 10


int main() {
    printf("Starting gentest...\n");

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 640, "gentest", NULL, NULL);

    if (!window) {
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int map[MAP_W*MAP_H] = {
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,3,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,3,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0
    };

    unsigned int atlas = load_texture();

    glOrtho(0, MAP_W*TILE_SIZE, MAP_H*TILE_SIZE, 0, -1, 1);

    Player player;
    player_init(&player, TILE_SIZE*2, TILE_SIZE*2, PLAYER_WIDTH, PLAYER_HEIGHT, 0.5f);
    player.texture = load_player();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_tilemap(atlas, map, MAP_W, MAP_H, TILE_SIZE);
        player_update(&player, window);
        player_draw(&player);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}