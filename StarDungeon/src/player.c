#include "player.h"

Player* createPlayer(int x, int y, const char* spritePath){

    SDL_Surface* playerSurface = NULL;

    Player* player = (Player*)malloc(sizeof(Player));
    player->player_transform = (Transform*)malloc(sizeof(Transform));
    player->player_transform->x = x;
    player->player_transform->y = y;   
    player->player_transform->w = 96; 
    player->player_transform->h = 96; 
    player->player_transform->speed = 0; 
    player->player_transform->scale_x = 3.5;
    player->player_transform->scale_y = 3.5;

    player->player_animation = (Animation*)malloc(sizeof(Animation));
    player->player_animation->speed = 0.1f;
    player->player_animation->frames = 4;
    player->player_animation->frameCount = 0;



    player->player_sbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    player->player_sbox->w = player->player_transform->w;
    player->player_sbox->h = player->player_transform->h;
    player->player_sbox->x = 0;
    player->player_sbox->y = 0;

    player->player_dbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    player->player_spriteController = NULL;

    if(ISNULL(spritePath)){
        printf("player sem textura\n");
        return player;        
    } 

    playerSurface = IMG_Load(spritePath);
    if(ISNULL(playerSurface)){
        printf("Nao foi possivel carregar a sprite do inimigo\n");
        return NULL;
    }
    player->player_texture = SDL_CreateTextureFromSurface(renderer, playerSurface);

    return player;

}

SpriteControll* createSpriteController(const char* spr0, const char* spr1, const char* spr2,  const char* spr3, const char* spr4){

    SpriteControll* spc = (SpriteControll*)malloc(sizeof(SpriteControll));
    strcpy(spc->spr0,  spr0);
    strcpy(spc->spr1,  spr1);
    strcpy(spc->spr2,  spr2);
    strcpy(spc->spr3,  spr3);
    strcpy(spc->spr4,  spr4);

    /* carregando todas as texturas */
    SDL_Surface* aux = NULL;

    /* IDLE */
    aux = IMG_Load(spc->spr0);
    spc->spr0_texture = SDL_CreateTextureFromSurface(renderer, aux);
    SDL_FreeSurface(aux);
    /* HIT */
    aux = IMG_Load(spc->spr1);
    spc->spr1_texture = SDL_CreateTextureFromSurface(renderer, aux);
    SDL_FreeSurface(aux);
    /* JUMP */
    aux = IMG_Load(spc->spr2);
    spc->spr2_texture = SDL_CreateTextureFromSurface(renderer, aux);
    SDL_FreeSurface(aux);
    /* RUN */
    aux = IMG_Load(spc->spr3);
    spc->spr3_texture = SDL_CreateTextureFromSurface(renderer, aux);
    SDL_FreeSurface(aux);
    /* DEATH */
    aux = IMG_Load(spc->spr4);
    spc->spr4_texture = SDL_CreateTextureFromSurface(renderer, aux);
    SDL_FreeSurface(aux);

    return spc;

}

SpriteStateControll* createSpriteStateControll(){
    SpriteStateControll* ssc = (SpriteStateControll*)malloc(sizeof(SpriteStateControll));
    return ssc;
}

void setPlayerSpriteController(Player* player, SpriteControll* spc){
    player->player_spriteController = spc;
}

void setSpriteState(Player* player, SpriteStateControll* ssc, const char* state){
    if(strcmp(ssc->state, state) != 0){
        resetFrameCount(player->player_animation);
        strcpy(ssc->state, state);
    }
}

const char* getSpriteState(SpriteStateControll* ssc){
    return ssc->state;
}

void renderPlayer(Player* player){

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    
    SDL_Rect aux = {
        player->player_transform->x,
        player->player_transform->y,
        player->player_sbox->w,
        player->player_sbox->h
    };

    SDL_RenderCopy(
        renderer,
        player->player_texture,
        NULL,
        &aux
    );

}

void renderPlayerAnimation(Player* player, SpriteStateControll* ssc){

    player->player_animation->frameCount++;
    int flip = 0;
    if(player->player_transform->direction < 0)
        flip = 1;

    if(strcmp("IDLE", ssc->state) == 0){
        
        player->player_texture = player->player_spriteController->spr0_texture;
        player->player_animation->frames = 4;

    }else if(strcmp("ATK", ssc->state) == 0){

        player->player_texture = player->player_spriteController->spr4_texture;
        player->player_animation->frames = 2;
        if(player->player_animation->currentFrame >= 1){
            setSpriteState(player, ssc, "IDLE");
        }

    }else if(strcmp("RUN", ssc->state) == 0){

        player->player_texture = player->player_spriteController->spr3_texture;        
        player->player_animation->frames = 6;

    }
    

    player->player_dbox->x = player->player_transform->x;
    player->player_dbox->y = player->player_transform->y;
    player->player_dbox->w = player->player_transform->w * player->player_transform->scale_x;
    player->player_dbox->h = player->player_transform->h * player->player_transform->scale_y;

    SDL_RenderCopyEx(
        renderer,
        player->player_texture,
        player->player_sbox,
        player->player_dbox,
        0,
        NULL,
        flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );



}

void updatePlayer(Player* player){

    int frame = (int)(player->player_animation->frameCount*player->player_animation->speed) % player->player_animation->frames;
    printf("current frame: %d\n", frame);
    player->player_animation->currentFrame = frame;
    player->player_sbox->x = player->player_sbox->w * player->player_animation->currentFrame;

}

void setPlayerSpeed(Player* player, float speed){
    player->player_transform->speed = speed;
}

void playerMovement(Player* player){    
    
    if(player->player_transform->speed != 0){
        
        if(player->player_transform->speed < 0){
            player->player_transform->direction = -1;
            if(player->player_transform->x > 0)
                player->player_transform->x += player->player_transform->speed * deltaTime * 10;
        }else if(player->player_transform->speed > 0){
            player->player_transform->direction = 1;
            if(player->player_transform->x < 640 - 100)
                player->player_transform->x += player->player_transform->speed * deltaTime * 10;
        }

    }

}