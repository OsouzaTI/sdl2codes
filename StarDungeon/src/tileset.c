#include "tileset.h"

Tileset* createTileset(int width, int height, int sizeGrid, const char* tilesetPath){
    SDL_Surface* tileset_surface = NULL; 

    Tileset* t = (Tileset*)malloc(sizeof(Tileset));
    t->width = width;
    t->height = height;
    t->sizeGrid = sizeGrid;

    tileset_surface = IMG_Load(tilesetPath);    
    if(!tileset_surface)return NULL;

    t->tileset_texture = SDL_CreateTextureFromSurface(renderer, tileset_surface);
    SDL_FreeSurface(tileset_surface);

    return t;

}

void renderTileset(int tposx, int tposy, int x, int y, Tileset* tileset){

    SDL_Rect saux = {
        tileset->sizeGrid * tposx,
        tileset->sizeGrid * tposy,
        tileset->sizeGrid,
        tileset->sizeGrid
    };

    SDL_Rect daux = {
        x * tileset->sizeGrid,
        y * tileset->sizeGrid,
        tileset->sizeGrid,
        tileset->sizeGrid
    };

    SDL_RenderCopy(renderer, tileset->tileset_texture, &saux, &daux);

}