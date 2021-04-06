#include "background.h"

Background* createBackground(const char* bgPath){

    SDL_Surface* bgSurface = NULL;

    Background* b = (Background*)malloc(sizeof(Background));
    b->bg_sbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    b->bg_sbox->x = 0;
    b->bg_sbox->y = 0;
    b->bg_sbox->w = WINDOW_WIDTH;
    b->bg_sbox->h = WINDOW_HEIGHT;

    bgSurface = IMG_Load(bgPath);
    if(!bgSurface){
        printf("nao foi possivel criar a bgSurface\n");
        return NULL;
    }

    b->bg_texture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    if(!b->bg_texture){
        printf("erro ao criar textura\n");
        return NULL;
    }
    
    SDL_FreeSurface(bgSurface);

    return b;
}

void destroyBackground(Background* background){

    free(background->bg_sbox);
    free(background);

}

void renderBackground(Background* bg){

    SDL_RenderCopy(renderer, bg->bg_texture, NULL, bg->bg_sbox);

}