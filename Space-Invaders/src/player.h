#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "constants.h"
#include "transform.h"

typedef struct player
{
    int life;
    Transform *player_transform;
    SDL_Rect* player_box;
    SDL_Texture* player_texture;
} Player;

Player* createPlayer(int x, int y, const char* spritePath);
void renderPlayer(Player* player);

#endif