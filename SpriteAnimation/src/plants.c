#include "plants.h"

Plants* createPlant(int x, int y, int time){

    SDL_Surface* surfacePlant = NULL;

    Plants* p = (Plants*)malloc(sizeof(Plants));

    p->plant_animation = (Animation*)malloc(sizeof(Animation));
    p->plant_animation->frames = 5;
    p->plant_animation->speed  = 1/(float)time;
    p->plant_animation->currentFrame  = 0;

    p->plant_transform = (Transform*)malloc(sizeof(Transform));
    p->plant_transform->x = x;
    p->plant_transform->y = y;
    p->plant_transform->w = 32;
    p->plant_transform->h = 32;
    p->plant_transform->scale_x = 3;
    p->plant_transform->scale_y = 3;

    p->plant_sbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    p->plant_sbox->x = 0; /* posicao relativa da texture */
    p->plant_sbox->y = 0;
    p->plant_sbox->w = p->plant_transform->w;
    p->plant_sbox->h = p->plant_transform->h;

    p->plant_dbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));


    surfacePlant = IMG_Load("F:\\Projects\\c\\SDL2\\SpriteAnimation\\assets\\img\\plant01.png");
    if(!surfacePlant){
        printf("nao foi possivel criar a surfacePlant\n");
        return NULL;
    }

    p->plant_texture = SDL_CreateTextureFromSurface(renderer, surfacePlant);
    SDL_FreeSurface(surfacePlant);

    return p;

}

void destroyPlant(Plants* plant){

    free(plant->plant_dbox);
    free(plant->plant_sbox);
    free(plant->plant_transform);
    free(plant->plant_animation);
    free(plant);

}

void renderPlant(Plants* plant){

    plant->plant_dbox->x = plant->plant_transform->x;
    plant->plant_dbox->y = plant->plant_transform->y;
    plant->plant_dbox->w = plant->plant_transform->w * plant->plant_transform->scale_x;
    plant->plant_dbox->h = plant->plant_transform->h * plant->plant_transform->scale_y;

    SDL_RenderCopy(
        renderer,
        plant->plant_texture,
        plant->plant_sbox,
        plant->plant_dbox
    );

}

void updatePlant(Plants* plant){
    int frame = 
        (int)((SDL_GetTicks()/1000)*plant->plant_animation->speed)
        %plant->plant_animation->frames;
    if(plant->plant_animation->currentFrame < plant->plant_animation->frames-1)
        plant->plant_animation->currentFrame = frame;
    plant->plant_sbox->x = plant->plant_sbox->w * plant->plant_animation->currentFrame;
}