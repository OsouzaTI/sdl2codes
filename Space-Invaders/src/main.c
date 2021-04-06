#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "display.h"
#include "enemy.h"
#include "player.h"
#include "label.h"
#include "projectile.h"

int previousFrameTime = 0;
int isRuning = 0;

lProjectile* listaDeProjetils;
lEnemy* enemyList;
Player* player;
Label* label;

void setup(){

    enemyList = createEnemyList();
    createAFixedNumberOfEnemies(enemyList, 10);

    player = createPlayer(
        WINDOW_WIDTH/2,
        WINDOW_HEIGHT - 128,
        "F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\images\\ovni.png"
    );

    label = createLabel("Delta Time: ", WINDOW_WIDTH - 130, 10);

    listaDeProjetils = createListProjectile();
    if(ISNULL(listaDeProjetils)){
        printf("nulaaaa\n");
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

}

void processInput(){
    
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:{
            isRuning = 0;
        }break;
        case SDL_KEYDOWN:{
            
            switch (event.key.keysym.sym)
            {    
                case SDLK_ESCAPE:{
                    isRuning = 0;
                }break;                
                case SDLK_LEFT:{
                    player->player_transform->x -= 120 * deltaTime;
                }break;                
                case SDLK_RIGHT:{                    
                    player->player_transform->x += 120 * deltaTime;
                }break;
                case SDLK_SPACE:{                    
                    
                    Projectile* newProjetil = createProjectile(
                        player->player_transform->x + 4,
                        player->player_transform->y - 32,
                        240
                    );

                    insertProjectileAtBegin(listaDeProjetils, newProjetil);

                    //Play the low hit effect
                    if( Mix_PlayChannel( -1, fx_shot, 0 ) == -1 )
                        printf("nao foi possivel executar o som de tiro\n");

                }break;
                default:{
                    
                }break;
            }

        }break;
        default:
        break;
    }

}

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), previousFrameTime + FRAME_TARGET_TIME));
    deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0f;
    previousFrameTime = SDL_GetTicks();

    char buffer[100];
    sprintf(buffer, "Delta Time: %.2f", deltaTime);
    setLabelText(label, buffer);


    if(gameOver(enemyList, player))
        destroyAllEnemys(enemyList);

    if(ISNULL(enemyList->first))
        createAFixedNumberOfEnemies(enemyList, 10);

}

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    detectProjectileCollision(listaDeProjetils, enemyList);
    /* atualiza posicao e renderiza */
    updateEnemies(enemyList);

    /* renderiza e verifica se saiu da tela */
    updateProjectiles(listaDeProjetils);

    renderPlayer(player);
    renderLabel(label);

    SDL_RenderPresent(renderer);


}

int main(int argc, char *argv[]){
    isRuning = InitializeWindow();
    printf("Welcome to Space Invaders\n");    

    setup();
    while(isRuning){
        processInput();
        update();
        render();
    }
    
    return 0;
}