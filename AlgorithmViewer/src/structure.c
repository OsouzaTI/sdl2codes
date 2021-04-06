#include "structure.h"

sNode *target = NULL;

vNode* createVisualNode(int x, int y, int key){
    SDL_Color RED = {255, 0 , 0, 255};
    char buffer[30];
    sprintf(buffer, "%d", key);

    vNode* n = (vNode*)malloc(sizeof(vNode));
    if(!n) return NULL;
    n->value = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    n->pointer = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    n->key = key;

    n->surface_text = TTF_RenderText_Blended(font, buffer , RED);
    n->texture_text = SDL_CreateTextureFromSurface(renderer, n->surface_text);

    n->value->x = x;
    n->value->y = y;
    n->value->w = 100;
    n->value->h = 50;

    n->pointer->x = x+75;
    n->pointer->y = y;
    n->pointer->w = 25;
    n->pointer->h = 50;

    return n;

}

void renderVisualNode(lNode* n){

    sNode *p;
    for(p = n->first;p;p = p->next){

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   
        SDL_RenderDrawRect(renderer, p->value->value);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, p->value->pointer);

    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void destroyVisualNode(vNode* n){
    free(n->value);
    free(n->pointer);
    free(n);
}

void linkVisualNode(lNode* l){

    int x1, y1, x2, y2;
    sNode *p, *q;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   
    for(p = l->first;p;p = p->next){
        if(ISNULL(p->next))break;
        q = p->next;
        x1 = p->value->pointer->x+10;
        y1 = p->value->pointer->y+25;
        x2 = q->value->value->x+25;
        y2 = q->value->value->y+25;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

}

void moveVisualNode(Mouse* m, lNode* l){
    
    SDL_Rect *a, *b;
    sNode *p;
    for(p = l->first;p;p = p->next){
        a = p->value->value;
        b = p->value->pointer;
        if(MOUSE(m->x, m->y, a->x, a->y, a->w, a->h)){
            
            SDL_PollEvent(&event);
            switch (event.type)
            {
                case SDL_MOUSEMOTION:{
                    if(event.button.button == SDL_BUTTON_LEFT){
                        if(ISNULL(target))
                            target = p;
                        if(ISEQUAL(p, target)){
                            a->x = m->x - 50;
                            a->y = m->y - 25;  
                            b->x = (a->x+a->w)-b->w;
                            b->y = (a->y+a->h)-b->h;
                        }
                    }
                }break;
                case SDL_MOUSEBUTTONUP:{
                    
                }break;
                default:
                    target = NULL;
                    break;
            }            
        }
    }

}

void renderVisualNodeText(lNode* l){
    sNode *p;
    for(p = l->first;p;p = p->next){
        SDL_Rect Message_rect = {
            p->value->value->x + 25,
            p->value->value->y + 10,
            30,
            30
        };
        SDL_RenderCopy(renderer, p->value->texture_text, NULL, &Message_rect);
    }
}

///////////////////////////////////////////////
/* Lista lincada de vNode */
///////////////////////////////////////////////

lNode* createLNode(){
    lNode* n = (lNode*)malloc(sizeof(lNode));
    n->first = NULL;
    return n;
}

void insertAtBegin(lNode* n, vNode* v){
    if(ISNULL(n))return;
    sNode* newsNode = (sNode*)malloc(sizeof(sNode));
    newsNode->value = v;
    newsNode->next = n->first;
    n->first = newsNode;
}

void insertAtEnd(lNode* n, vNode* v){
    if(ISNULL(n))return;
    sNode* newsNode = (sNode*)malloc(sizeof(sNode));
    newsNode->value = v;
    newsNode->next = NULL;

    if(ISNULL(n->first)){
        n->first = newsNode;
        return;
    }

    sNode* p;
    for(p = n->first;!ISNULL(p);p = p->next){
        if(ISNULL(p->next))break;
    }
    p->next = newsNode;
}

void cleanLNode(lNode* l){

    sNode* p;
    for(p = l->first;p;p = p->next)
        destroyVisualNode(p->value);

}