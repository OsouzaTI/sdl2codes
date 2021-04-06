#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "display.h"

typedef struct Text
{
    SDL_Surface* surface_text;
    SDL_Texture* texture_text;
} Text;

Text* createLabel(const char* text);
void renderLabel(Text* t, int x, int y, int w, int h);
void destroyLabel(Text* l);

#endif