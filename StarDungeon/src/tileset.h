#ifndef TILESET_H
#define TILESET_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "display.h"

typedef struct tileset
{
    int width;
    int height;
    int sizeGrid;
    SDL_Texture* tileset_texture;
} Tileset;


Tileset* createTileset(int width, int height, int sizeGrid, const char* tilesetPath);
void renderTileset(int tposx, int tposy, int x, int y, Tileset* tileset);

#endif