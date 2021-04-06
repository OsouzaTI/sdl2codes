#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "camera.h"

typedef struct background
{
    SDL_Rect* bg_sbox;
    SDL_Rect* bg_dbox;
    SDL_Texture* bg_texture;
} Background;

Background* createBackground(const char* bgPath);
void renderBackground(Background* bg);
void renderBackgroundCamera(Background* bg, Camera* camera);
void destroyBackground(Background* background);
#endif