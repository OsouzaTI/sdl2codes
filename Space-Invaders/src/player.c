#include "player.h"

Player* createPlayer(int x, int y, const char* spritePath){

    SDL_Surface* playerSurface = NULL;

    Player* player = (Player*)malloc(sizeof(Player));
    player->player_box = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->player_transform = (Transform*)malloc(sizeof(Transform));
    player->player_transform->x = x;
    player->player_transform->y = y;    
    player->player_box->w = 32;
    player->player_box->h = 32;
    player->player_box->x = x;
    player->player_box->y = y;

    playerSurface = IMG_Load(spritePath);
    if(ISNULL(playerSurface)){

        printf("Nao foi possivel carregar a sprite do inimigo\n");
        return NULL;

    }

    player->player_texture = SDL_CreateTextureFromSurface(renderer, playerSurface);

    return player;

}

void renderPlayer(Player* player){

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    
    SDL_Rect aux = {
        player->player_transform->x,
        player->player_transform->y,
        player->player_box->w,
        player->player_box->h
    };

    SDL_RenderCopy(
        renderer,
        player->player_texture,
        NULL,
        &aux
    );

}