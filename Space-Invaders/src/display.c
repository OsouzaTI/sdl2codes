#include "display.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Window   *window  = NULL; 
SDL_Renderer *renderer  = NULL;
SDL_Surface  *windowSurface = NULL;
TTF_Font     *font = NULL;
TTF_Font     *hud = NULL;
SDL_Event    event;
float        deltaTime = 0.0f;
int         WINDOW_WIDTH = 960;
int         WINDOW_HEIGHT = 540;

/* Sounds effects */
Mix_Chunk *fx_shot = NULL;
Mix_Chunk *fx_spaceKilled = NULL;

int InitializeWindow(void){

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL.\n");
        return 0;
    }
      
    if(TTF_Init() == -1){
        return 0;
    }
    
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
        return 0;
    }

    /* load sounds */
    fx_shot = Mix_LoadWAV("F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\sounds\\laser.wav");
    fx_spaceKilled = Mix_LoadWAV("F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\sounds\\invaderkilled.wav");

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }

    window = SDL_CreateWindow(
        "Invasores de casadas",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_MOUSE_CAPTURE
    );

    font = TTF_OpenFont("F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\fonts\\Minecraft.ttf", 20);
    
    if(font == NULL){
        printf("erro ao abrir font\n");
        return (0);
    }

    if(!window){
        printf("Error create SDL window.\n");
        return 0;
    }
    
    windowSurface = SDL_GetWindowSurface(window);

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        printf("Error create SDL renderer.\n");
        return 0;
    }
    
    return 1;
}
