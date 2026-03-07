#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>

typedef struct {
    float x, y;
    int width, height;
    float speed;
    unsigned int texture;
} Player;

void player_init(Player* p, float x, float y, int width, int height, float speed);
void player_update(Player* p, GLFWwindow* window);
void player_draw(Player* p);
unsigned int load_player();

#endif