#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "display.h"
#include "background.h"
#include "camera.h"
#include "player.h"

void setup();

int previousFrameTime = 0;
int isRuning = 0;
Background* bg;
Camera* camera;
Player* player;
SpriteControll* spc;
SpriteControll* spcH;
SpriteStateControll* ssc;

void setup(){
    
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEWHEEL, SDL_IGNORE);

    bg = createBackground("F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\mapa.png");
    camera = createCamera(0, 0, 150, 100);
    player = createPlayer(32, 32, NULL);

    spc = createSpriteController(
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\player\\Idle.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\player\\Hit.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\player\\Jump.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\player\\Run.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\player\\Death.png"
    );

    spcH = createSpriteController(
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\playerH\\Idle_H.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\playerH\\Hit.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\playerH\\Jump_H.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\playerH\\Run_H.png",
        "F:\\Projects\\c\\SDL2\\StarDungeon\\assets\\img\\playerH\\Attack1_H.png"
    );

    ssc = createSpriteStateControll();
    setSpriteState(player, ssc, "IDLE");
    
    setPlayerSpriteController(player, spc);

}

void processInput(){

    while(SDL_PollEvent(&event)){

        switch(event.type){

            case SDL_KEYDOWN:{

                int speed = 50;
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:{
                        setPlayerSpeed(player, -speed);
                        setSpriteState(player, ssc, "RUN");
                    }break;
                    case SDLK_RIGHT:{
                        setPlayerSpeed(player,  speed);
                        setSpriteState(player, ssc, "RUN");
                    }break;
                    case SDLK_f:{
                        setPlayerSpriteController(player, spc);
                    }break;
                }

            }break;
            case SDL_MOUSEBUTTONDOWN: {
                if(strcmp(getSpriteState(ssc), "ATK") != 0){
                    if(event.button.button == SDL_BUTTON_LEFT){
                        setPlayerSpriteController(player, spcH);
                        setSpriteState(player, ssc, "ATK");              
                    }
                }

            }break;
            case SDL_QUIT:{
                isRuning = 0;
            }break;
            default:{
                setPlayerSpeed(player,  0);
                setSpriteState(player, ssc, "IDLE");
            }break;

        }

    }
}

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), previousFrameTime + FRAME_TARGET_TIME));
    deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    previousFrameTime = SDL_GetTicks();

    moveCamera(camera, bg->bg_sbox, player->player_transform);

    updatePlayer(player);	
    playerMovement(player);

}

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    renderBackgroundCamera(bg, camera);
    renderPlayerAnimation(player, ssc);

    SDL_Rect cam = {
        camera->camera_transform->x,
        camera->camera_transform->y,
        camera->camera_transform->w,
        camera->camera_transform->h
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, bg->bg_sbox);

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