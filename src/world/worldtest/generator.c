#include <SDL2/SDL.h>
#include "perlin/noise1234.h"

#define MAP_SIZE 100
#define TILE_SIZE 6

typedef enum {
    TILE_WATER,
    TILE_SAND,
    TILE_GRASS,
    TILE_DESERT,
    TILE_STONE,
    TILE_FOREST
} TileType;

TileType map[MAP_SIZE][MAP_SIZE];

void generate_map() {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            double n = noise2(x * 0.1, y * 0.1);

            if (n < 0.2) map[y][x] = TILE_GRASS;
            else map[y][x] = TILE_WATER;
        }
    }

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (map[y][x] == TILE_GRASS) {
                int has_water_neighbor = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < MAP_SIZE && ny >= 0 && ny < MAP_SIZE) {
                            if (map[ny][nx] == TILE_WATER) has_water_neighbor = 1;
                        }
                    }
                }
                if (has_water_neighbor) map[y][x] = TILE_SAND;
            }
        }
    }

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (map[y][x] == TILE_GRASS) {
                double biome = noise2(x * 0.03, y * 0.03);
                if (biome < -0.15)
                    map[y][x] = TILE_STONE;
                else if (biome < 0.0)
                    map[y][x] = TILE_FOREST;
                else if (biome < 0.15)
                    map[y][x] = TILE_GRASS;
                else
                    map[y][x] = TILE_DESERT;
            }
        }
    }
}

void draw_map(SDL_Renderer* renderer) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            switch (map[y][x]) {
                case TILE_WATER:  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
                case TILE_SAND:   SDL_SetRenderDrawColor(renderer, 194, 178, 128, 255); break;
                case TILE_GRASS:  SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); break;
                case TILE_FOREST: SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); break;
                case TILE_DESERT: SDL_SetRenderDrawColor(renderer, 237, 201, 175, 255); break;
                case TILE_STONE:  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); break;
            }

            SDL_Rect r = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderFillRect(renderer, &r);
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "World Test/Map Prototype",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        MAP_SIZE*TILE_SIZE,
        MAP_SIZE*TILE_SIZE,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    generate_map();

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        draw_map(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}