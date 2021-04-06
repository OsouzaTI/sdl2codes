#ifndef ENEMY_H
#define ENEMY_H


#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "display.h"
#include "transform.h"
#include "logs.h"
#include "player.h"

typedef struct Origin
{
    int x;
    int y;
} Origin;

typedef struct enemy
{
    int life;
    Origin* enemy_origin;
    Transform* enemy_transform;
    SDL_Rect* enemy_box;
    SDL_Texture* enemy_texture;
} Enemy;

typedef struct nEnemy
{
    Enemy* value;
    struct nEnemy* next;
} nEnemy;

typedef struct lEnemy
{
    nEnemy* first;
} lEnemy;



Enemy* createEnemy(int life, int x, int y, const char* spritePath);
void createAFixedNumberOfEnemies(lEnemy* enemies, int numberOfInstances);
void renderEnemy(Enemy* enemy);
void moveEnemy(Enemy* enemy);
void updateEnemies(lEnemy* enemies);
void destroyEnemy(Enemy* enemy);
int gameOver(lEnemy* enemies, Player* player);
void destroyAllEnemys(lEnemy* enemy);
/* lista lincada */
lEnemy* createEnemyList();
void insertEnemyAtBegin(lEnemy* l, Enemy* n);
void removeEnemyAtPosition(lEnemy* enemys, Enemy* enemy);
Enemy* enemyAtPosition(lEnemy* enemys, int pos);
#endif