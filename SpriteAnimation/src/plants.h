#ifndef PLANTS_H
#define PLANTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "transform.h"
#include "animation.h"

typedef struct plants
{   
    Animation* plant_animation;
    Transform* plant_transform;
    SDL_Rect* plant_sbox; 
    SDL_Rect* plant_dbox; 
    SDL_Texture* plant_texture;
} Plants;

Plants* createPlant(int x, int y, int time);
void renderPlant(Plants* plant);
void updatePlant(Plants* plant);
void destroyPlant(Plants* plant);
#endif