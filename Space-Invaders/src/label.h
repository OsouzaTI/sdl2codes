#ifndef LABEL_H
#define LABEL_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "display.h"
#include "constants.h"

extern SDL_Color C_GREEN;

typedef struct label
{
    char *text;
    int x;
    int y;
    SDL_Rect* rect_text;
    SDL_Texture* texture_text;
} Label;

Label* createLabel(const char* text, int x, int y);
void setLabelText(Label* label, const char* text);
void renderLabel(Label* label);


#endif