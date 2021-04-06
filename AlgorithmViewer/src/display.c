#include "display.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Window   *window  = NULL; 
SDL_Renderer *renderer  = NULL;
TTF_Font     *font = NULL;
TTF_Font     *hud = NULL;
SDL_Event    event;
int  WINDOW_WIDTH = 1000;
int  WINDOW_HEIGHT = 800;

int InitializeWindow(void){

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL.\n");
        return 0;
    }
      
    if(TTF_Init() == -1){
        return 0;
    }
  
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

    return 1;
}
