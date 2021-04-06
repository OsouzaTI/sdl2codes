#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "display.h"
#include "plants.h"
#include "background.h"
#include "particles.h"

void setup();

int previousFrameTime = 0;
int isRuning = 0;

#define MAX_PLANTS 20
#define MAX_PARTICLES 10
Plants *plant[MAX_PLANTS];
Background* bg;

/* Particulas */
ParticleEmitter* emitter[MAX_PARTICLES];
Particles *particles[MAX_PARTICLES];

void setup(){

    bg = createBackground("F:\\Projects\\c\\SDL2\\SpriteAnimation\\assets\\img\\field02.png");
    
    for(int i = 0; i < MAX_PLANTS; i++){
        emitter[i] = createParticleEmitter(rand()%WINDOW_WIDTH - 100, -10, rand()%80+30);
        particles[i] = createParticle(emitter[i]);
    }
    

    for(int i = 0; i < MAX_PLANTS; i++){
        plant[i] = createPlant(
            rand()%(WINDOW_WIDTH-100),
            rand()%(WINDOW_HEIGHT-100),
            10 + rand()%10+ rand()%20 + rand()%30
        );
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
    deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0f;
    previousFrameTime = SDL_GetTicks();
	
}

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    renderBackground(bg);

    for(int i = 0; i < MAX_PLANTS; i++){
        updatePlant(plant[i]);
        renderPlant(plant[i]);
    }

    for(int i = 0; i < MAX_PARTICLES; i++){
        moveParticles(particles[i]);
        renderParticles(particles[i]);        
    }
    

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