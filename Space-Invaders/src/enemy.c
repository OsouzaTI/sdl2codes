#include "enemy.h"

Enemy* createEnemy(int life, int x, int y, const char* spritePath){
    SDL_Surface* enemySurface = NULL;

    Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->enemy_box = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    enemy->enemy_origin = (Origin*)malloc(sizeof(Origin));
    enemy->enemy_transform = (Transform*)malloc(sizeof(Transform));
    enemy->enemy_transform->direction = 1;
    enemy->enemy_transform->x = x;
    enemy->enemy_transform->y = y;    
    enemy->enemy_box->w = 32;
    enemy->enemy_box->h = 32;
    enemy->enemy_box->x = x;
    enemy->enemy_box->y = y;
    enemy->enemy_origin->x = x;
    enemy->enemy_origin->y = y;

    enemySurface = IMG_Load(spritePath);
    if(ISNULL(enemySurface)){

        printf("Nao foi possivel carregar a sprite do inimigo\n");
        return NULL;

    }

    enemy->enemy_texture = SDL_CreateTextureFromSurface(renderer, enemySurface);
    SDL_FreeSurface(enemySurface);

    return enemy;

}

void createAFixedNumberOfEnemies(lEnemy* enemies, int numberOfInstances){

    int i;
    for(i = 0; i < 10; i++){
        Enemy* enemy = createEnemy(
            10,
            (WINDOW_WIDTH/4-64) + (64 * i),
            64,
            "F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\images\\enemigo2.png"
        );
        insertEnemyAtBegin(enemies, enemy);
    }

}


void renderEnemy(Enemy* enemy){

    SDL_Rect aux = {
        enemy->enemy_transform->x,
        enemy->enemy_transform->y,
        enemy->enemy_box->w,
        enemy->enemy_box->h
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer,& aux);

    SDL_RenderCopy(
        renderer,
        enemy->enemy_texture,
        NULL,
        &aux
    );

}

void moveEnemy(Enemy* enemy){
    int time = SDL_GetTicks();
    int radius = 100;
    if(
        enemy->enemy_transform->x > (enemy->enemy_origin->x + radius)||
        enemy->enemy_transform->x < (enemy->enemy_origin->x - radius)
    ){
        /* muda a diracao do inimigo */
        enemy->enemy_transform->direction *= -1;
    }

    enemy->enemy_transform->x += 20.0f * deltaTime * enemy->enemy_transform->direction;
    if((int)(time/1000.0f)%10==0 && time != 0){
        enemy->enemy_transform->y += 40 * deltaTime;
    }

}

void destroyEnemy(Enemy* enemy){

    free(enemy->enemy_transform);
    free(enemy->enemy_origin);
    free(enemy->enemy_box);
    SDL_DestroyTexture(enemy->enemy_texture);
    free(enemy);
    
}

void destroyAllEnemys(lEnemy* enemys){

    nEnemy *p;
    for (p = enemys->first; !ISNULL(p); p = p->next) {
        removeEnemyAtPosition(enemys, 0);
        break;
    }

}

int gameOver(lEnemy* enemies, Player* player){
    int i;
    nEnemy *p;
    for (p = enemies->first; !ISNULL(p); p = p->next) {
        if(p->value->enemy_transform->y > player->player_transform->y){
            return 1;
        }
    }
    return 0;

}

void updateEnemies(lEnemy* enemies){

    nEnemy *p;
    for (p = enemies->first; !ISNULL(p); p = p->next){
        moveEnemy(p->value);
        renderEnemy(p->value);
    }

}


/* lista lincada */
lEnemy* createEnemyList(){
    lEnemy* n = (lEnemy*)malloc(sizeof(lEnemy));
    n->first = NULL;
    return n;
}

void insertEnemyAtBegin(lEnemy* l, Enemy* n){

    nEnemy* newsNode = (nEnemy*)malloc(sizeof(nEnemy));
    if(ISNULL(newsNode)){
        logs(ERROR, "erro ao alocar memoria para o no de projetil");
    }

    newsNode->value = n;
    newsNode->next = l->first;
    l->first = newsNode;

}

void removeEnemyAtPosition(lEnemy* enemys, Enemy* enemy){
  
    unsigned char keyExists = 0;
    nEnemy* p = NULL;
    nEnemy* q = NULL;
    
    if (ISNULL(enemys->first))return;

    if (ISNULL(enemys->first->next)) {        
        destroyEnemy(enemys->first->value);       
        free(enemys->first);       
        enemys->first = NULL;
        return;
    }

    p = enemys->first;
    while (p) {
        if (!ISNULL(p) && ISEQUAL(p->value, enemy)) {
            if (ISNULL(q)) {
                enemys->first = p->next;
                destroyEnemy(p->value);
                free(p);
                return;
            }
            q->next = p->next;
            destroyEnemy(p->value);
            free(p);
            return;
        }
        q = p;
        p = p->next;
    }
   


}

Enemy* enemyAtPosition(lEnemy* enemys, int pos)
{
    /* recupera um nodo em uma posicao especifica */
    nEnemy* p;
    int aux = 0;
    for (p = enemys->first; !ISNULL(p); p = p->next) {
        if (ISEQUAL(aux, pos)) {
            return p->value;
        }
        aux++;
    }
    printf("index not found\n");
    return NULL;

}
