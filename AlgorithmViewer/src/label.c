#include "label.h"



Text* createLabel(const char* text){
    Text* t = (Text*)malloc(sizeof(Text));
    SDL_Color GREEN = {0, 255, 0 , 255};
    t->surface_text = TTF_RenderText_Blended(font, text, GREEN);
    t->texture_text = SDL_CreateTextureFromSurface(renderer, t->surface_text);
    return t;
}

void renderLabel(Text* t, int x, int y, int w, int h){ 
    SDL_Rect Message_rect = { x, y, w, h };    
    SDL_RenderCopy(renderer, t->texture_text, NULL, &Message_rect);
}

void destroyLabel(Text* l){

    SDL_FreeSurface(l->surface_text);
    SDL_DestroyTexture(l->texture_text);
    free(l);

}