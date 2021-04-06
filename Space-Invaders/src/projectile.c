#include "projectile.h"

Projectile* createProjectile(int x, int y, float speed){

    SDL_Surface *surfaceProjectile = NULL;

    Projectile* projectile = (Projectile*)malloc(sizeof(Projectile));  
    projectile->projectile_transform = (Transform*)malloc(sizeof(Transform));
    projectile->projectile_transform->x = x;
    projectile->projectile_transform->y = y;
    projectile->velocity = speed;

    surfaceProjectile = IMG_Load("F:\\Projects\\c\\SDL2\\Space-Invaders\\assets\\images\\bala.png");
    if(ISNULL(surfaceProjectile)){
        printf("nao foi possivel criar o projetil\n");
        return NULL;
    }

    projectile->projectile_texture = SDL_CreateTextureFromSurface(renderer, surfaceProjectile);
    SDL_FreeSurface(surfaceProjectile);

    return projectile;

}

void moveProjectile(Projectile* projectile){

    projectile->projectile_transform->y -= projectile->velocity * deltaTime;

}

void renderProjectile(Projectile* projectile){
    int scale = 5;
    SDL_Rect aux = {
        (int)projectile->projectile_transform->x,
        (int)projectile->projectile_transform->y,
        1 * scale,
        8 * scale,
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer,& aux);

    SDL_RenderCopy(renderer, projectile->projectile_texture, NULL, &aux);

}

void updateProjectiles(lProjectile* projectile){

    int i = 0;
    nProjectile* p;
    for(p = projectile->first; !ISNULL(p) ; p = p->next){
        moveProjectile(p->value);
        renderProjectile(p->value);
        if(projectilesOutsideScreen(p->value)){
            removeProjectileAtPosition(projectile, i);
        }
        i++;
    }

}

void destroyProjectile(Projectile* projectile){

    free(projectile->projectile_transform);
    SDL_DestroyTexture(projectile->projectile_texture);
    free(projectile);

}

int projectilesOutsideScreen(Projectile* projectile) {
    if (projectile->projectile_transform->y < -64)
        return 1;
    return 0;
}

void detectProjectileCollision(lProjectile* projectile, lEnemy* enemys){
    
    if (ISNULL(projectile->first) || ISNULL(enemys->first))return;

    int i;
    int j;
    nEnemy* p;
    nProjectile* q;
    for (q = projectile->first; !ISNULL(q) ; q = q->next)
    {
        i = 0;
        for (p = enemys->first; !ISNULL(p) ; p = p->next)
        {    

            int enemy_x = p->value->enemy_transform->x;
            int enemy_y = p->value->enemy_transform->y;
            int enemy_w = p->value->enemy_box->w;
            int enemy_h = p->value->enemy_box->h;
            int projectile_x = q->value->projectile_transform->x;
            int projectile_y = q->value->projectile_transform->y;

            SDL_Rect aux = {
                enemy_x,
                enemy_y,
                enemy_w,
                enemy_h
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer,& aux);

            if(COLLISION_CHECK(enemy_x, enemy_y, projectile_x, projectile_y, enemy_w, enemy_w)){                
                //Play the low hit effect
                if( Mix_PlayChannel( -1, fx_spaceKilled, 0 ) == -1 )
                    printf("nao foi possivel executar o som de tiro\n");
                printf("acertou o %d\n", i);
                removeEnemyAtPosition(enemys, enemyAtPosition(enemys, i));    
                break;
            }
            i++;
        }
    }

}

/* Lista lincada */

lProjectile* createListProjectile(){

    lProjectile* l = (lProjectile*)malloc(sizeof(lProjectile));
    if(ISNULL(l)){
        logs(ERROR, "erro ao alocar memoria para projetil");
    }

    l->first = NULL;

    return l;

}

void insertProjectileAtBegin(lProjectile* l, Projectile* n){

    nProjectile* newsNode = (nProjectile*)malloc(sizeof(nProjectile));
    if(ISNULL(newsNode)){
        logs(ERROR, "erro ao alocar memoria para o no de projetil");
    }

    newsNode->value = n;
    newsNode->next = l->first;
    l->first = newsNode;

}

void removeProjectileAtPosition(lProjectile* projectile, int pos) {

    unsigned char keyExists = 0;
    nProjectile* p = NULL;
    nProjectile* q = NULL;

    if (ISNULL(projectile->first))return;

    if (ISNULL(projectile->first->next)) {
        destroyProjectile(projectile->first->value);
        free(projectile->first);
        projectile->first = NULL;
        return;
    }

    int i = 0;
    p = projectile->first;
    while (p) {
        q = p;
        p = p->next;
        if (!ISNULL(p) && ISEQUAL(i, pos)) {
            q->next = p->next;
            destroyProjectile(p->value);
            free(p);
            return;
        }
        i++;
    }

}