#include "display.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Window   *window  = NULL; 
SDL_Renderer *renderer  = NULL;
TTF_Font     *font = NULL;
TTF_Font     *hud = NULL;
SDL_Event    event;
float        deltaTime;
int  WINDOW_WIDTH  = 640;
int  WINDOW_HEIGHT = 480;
SDL_DisplayMode screenMode;

/* Sounds effects */
Mix_Chunk *fx_yamete = NULL;

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
    fx_yamete = Mix_LoadWAV("F:\\Projects\\c\\SDL2\\AlgorithmSort\\sound\\yamete.wav");

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }

    // SDL_GetCurrentDisplayMode(0, &screenMode);
    // WINDOW_WIDTH  = screenMode.w;
    // WINDOW_HEIGHT = screenMode.h;

    window = SDL_CreateWindow(
        "Teste",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_MOUSE_CAPTURE
    );

    font = TTF_OpenFont("F:\\Projects\\c\\SDL2\\AlgorithmViewer\\fonts\\Minecraft.ttf", 20);
    hud  = TTF_OpenFont("F:\\Projects\\c\\SDL2\\AlgorithmViewer\\fonts\\OldLondon.ttf", 18);
    if(font == NULL){
        printf("erro ao abrir font\n");
        return (0);
    }

    if(!window){
        printf("Error create SDL window.\n");
        return 0;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        printf("Error create SDL renderer.\n");
        return 0;
    }



    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return 1;
}
