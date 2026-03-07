#include "player.h"
#include "player_sprite.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void player_init(Player* p, float x, float y, int width, int height, float speed) {
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->speed = speed;
}

void player_update(Player* p, GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) p->y -= p->speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) p->y += p->speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) p->x -= p->speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) p->x += p->speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) p->speed * 2;
}

void player_draw(Player* p) {
    glBindTexture(GL_TEXTURE_2D, p->texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(p->x, p->y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(p->x + p->width, p->y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(p->x + p-> width, p->y + p->height);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(p->x, p->y + p->height);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

unsigned int load_player() {
    int width, height, channels;
    unsigned char* data = stbi_load_from_memory(player_png, player_png_len, &width, &height, &channels, 4);
    if (!data) {
        printf("Failed to load player texture\n");
        return 0;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture;
}