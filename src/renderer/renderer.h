#ifndef RENDERER_H
#define RENDERER_H

#include <GL/gl.h>

unsigned int load_texture();
void draw_tilemap(unsigned int texture, int* map, int map_width, int map_height, int tile_size);

#endif