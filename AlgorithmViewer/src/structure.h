#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "display.h"

#define ISNULL(x) (x == NULL)
#define ISEQUAL(x, y) (x == y)
#define MOUSE(mx, my, x, y, w, h) (mx >= x && mx < (x+w))&&(my >= y && my < (y+h))

typedef struct sNode sNode;
typedef struct vNode vNode;
typedef struct lNode lNode;

typedef struct vNode
{
    int key;
    SDL_Rect* value;
    SDL_Rect* pointer;
    SDL_Surface* surface_text;
    SDL_Texture* texture_text;
} vNode;

/* cabeca da lista */
typedef struct lNode
{
    sNode* first;
} lNode;

/* no de visualNodes */
typedef struct sNode
{
    vNode* value;
    struct sNode* next;    
} sNode;

typedef struct mouse
{
    int x;
    int y;
} Mouse;

extern int grab;
extern sNode* target;

vNode* createVisualNode(int x, int y, int key);
void renderVisualNode(lNode* n);
void destroyVisualNode(vNode* n);
void linkVisualNode(lNode* l);
void moveVisualNode(Mouse* m, lNode* l);
void renderVisualNodeText(lNode* l);
/* Lista lincada de vNode */
lNode* createLNode();
void insertAtBegin(lNode* n, vNode* v);
void insertAtEnd(lNode* n, vNode* v);
void cleanLNode();

#endif