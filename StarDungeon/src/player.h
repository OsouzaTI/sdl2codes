#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "display.h"
#include "constants.h"
#include "transform.h"
#include "animation.h"

#define MAX_STRING_PATH_BUFFER 100
#define MAX_STRING_STATE_BUFFER 32

typedef struct spriteControll SpriteControll;

typedef struct player
{
    int life;
    Transform *player_transform;
    SDL_Rect* player_sbox;
    SDL_Rect* player_dbox;
    SDL_Texture* player_texture;

    SpriteControll* player_spriteController;
    Animation* player_animation;
} Player;

typedef struct spriteControll
{
    char spr0[MAX_STRING_PATH_BUFFER];
    char spr1[MAX_STRING_PATH_BUFFER];
    char spr2[MAX_STRING_PATH_BUFFER];
    char spr3[MAX_STRING_PATH_BUFFER];
    char spr4[MAX_STRING_PATH_BUFFER];

    SDL_Texture* spr0_texture;
    SDL_Texture* spr1_texture;
    SDL_Texture* spr2_texture;
    SDL_Texture* spr3_texture;
    SDL_Texture* spr4_texture;

} SpriteControll;

typedef struct spriteStateControll
{
    char state[MAX_STRING_STATE_BUFFER];
} SpriteStateControll;


Player* createPlayer(int x, int y, const char* spritePath);
SpriteControll* createSpriteController(
    const char* spr0,
    const char* spr1,
    const char* spr2,
    const char* spr3,
    const char* spr4
);
void setPlayerSpriteController(Player* player, SpriteControll* spc);
SpriteStateControll* createSpriteStateControll();
void setSpriteState(Player* player, SpriteStateControll* ssc, const char* state);
const char* getSpriteState(SpriteStateControll* ssc);
void renderPlayer(Player* player);
void renderPlayerAnimation(Player* player, SpriteStateControll* ssc);
void updatePlayer(Player* player);
void setPlayerSpeed(Player* player, float speed);
void playerMovement(Player* player);

#endif