#ifndef PROJECTILE_H
#define PROJECTILE_H

#define COLLISION_CHECK(ex, ey, px, py, ew, eh) (px >= ex && px < (ex+ew))&&(py <= (ey+eh) && py > ey)

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "transform.h"
#include "constants.h"
#include "display.h"
#include "logs.h"
#include "enemy.h"

typedef struct projectile
{
    float velocity;
    Transform* projectile_transform;
    SDL_Texture* projectile_texture;
} Projectile;

typedef struct nProjectile{
    Projectile* value;
    struct nProjectile* next;
} nProjectile;

typedef struct lProjectile
{
    nProjectile* first;
} lProjectile;


Projectile* createProjectile(int x, int y, float speed);
void moveProjectile(Projectile* projectile);
void renderProjectile(Projectile* projectile);
void updateProjectiles(lProjectile* projectile);
void destroyProjectile(Projectile* projectile);
int  projectilesOutsideScreen(Projectile* projectile);
void detectProjectileCollision(lProjectile* projectile, lEnemy* enemys);
/* Lista lincada de projetils */
lProjectile* createListProjectile();
void insertProjectileAtBegin(lProjectile* l, Projectile* n);
void removeProjectileAtPosition(lProjectile* projectile, int pos);
#endif