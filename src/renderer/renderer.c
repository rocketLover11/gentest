#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
#include "tilemap.h"
#include "stb_image.h"
#include <GL/gl.h>
#include <stdio.h>

unsigned int load_texture() {
    int width, height, channels;
    unsigned char* data = stbi_load_from_memory(tilemap_png, tilemap_png_len, &width, &height, &channels, 4);
    if (!data) {
        printf("Failed to load textures");
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

void draw_tile(unsigned int texture, int tile_id, float x, float y, int tile_size) {
    int tiles_per_row = 5;
    float u = tile_id / (float)tiles_per_row;
    float du = 1.0f / tiles_per_row;

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(u, 0);
    glVertex2f(x, y);

    glTexCoord2f(u + du, 0);
    glVertex2f(x + tile_size, y);

    glTexCoord2f(u + du, 1);
    glVertex2f(x + tile_size, y + tile_size);
    
    glTexCoord2f(u, 1);
    glVertex2f(x, y + tile_size);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void draw_tilemap(unsigned int texture, int* map, int map_width, int map_height, int tile_size) {
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            int tile_id = map[y * map_width + x];
            draw_tile(texture, tile_id, x * tile_size, y * tile_size, tile_size);
        }
    }
}