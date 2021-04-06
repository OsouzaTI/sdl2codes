#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "display.h"

void setup();

int previousFrameTime = 0;
int isRuning = 0;

#define BAR_WIDTH 10
#define MAX ((int)(WINDOW_WIDTH/(BAR_WIDTH+5)))

int numeros[MAX];


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void drawBar(){
    
    for(int i = 0; i < MAX; i++){

        SDL_Rect aux = {
            i * 15,
            numeros[i],
            BAR_WIDTH,
            WINDOW_HEIGHT - numeros[i]
        };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &aux);

    }

}

void bubbleSort(int *v, int n){
    int reset = 1;
    if(n < 1)return;

    for(int i = 0; i < n; i++){
        if(v[i] > v[i+1]){
            swap(&v[i], &v[i+1]);
            reset = 0;
        }
    }

    if(reset)setup();
}

void selectionSort(int *v, int n){

    int i, j, min, aux, reset = 1;
    for(i = 0; i < n-1; i++){
        min = i;
        for(j =(i+1); j < n; j++){
            if(v[j] < v[min])
                min = j;
        }
        if(i != min){
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
            reset = 0;            
            break;
        }
    }
    

    if(reset){
        setup();
        return;
    }

    SDL_Rect raux = {
        i * 15,
        numeros[i],
        BAR_WIDTH,
        WINDOW_HEIGHT - numeros[i]
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &raux);

    //Play the low hit effect
    // if(Mix_PlayChannel(-1, fx_yamete, 0 ) == -1)
    //     printf("nao foi possivel executar o som de tiro\n");

}


void setup(){

    for(int i = 0; i < MAX; i++){
        numeros[i] = rand()%WINDOW_HEIGHT;
    }

}

void processInput(){
    
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRuning = 0;
            break;
    }

}

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), previousFrameTime + FRAME_TARGET_TIME));
    previousFrameTime = SDL_GetTicks();
}

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    drawBar();
    //bubbleSort(numeros, MAX-1);
    selectionSort(numeros, MAX);
    SDL_RenderPresent(renderer);

}

int main(int argc, char *argv[]){
    isRuning = InitializeWindow();
    printf("hello SDL2\n");    
    setup();
    while(isRuning){
        processInput();
        update();
        render();
    }
    return 0;
}