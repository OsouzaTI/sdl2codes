#include "label.h"

SDL_Color C_GREEN = {0, 255, 0, 255};

Label* createLabel(const char* text, int x, int y){

    Label* label = (Label*)malloc(sizeof(Label));
    label->rect_text = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    label->rect_text->w = 120;
    label->rect_text->h = 30;
    label->rect_text->x = x;
    label->rect_text->y = y;    
    
    label->text = (char*)malloc(sizeof(char)*strlen(text));
    strcpy(label->text, text);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, label->text, C_GREEN);
    if(ISNULL(textSurface)){
        printf("nao foi possivel criar a surface do label\n");
        return NULL;
    }

    label->texture_text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return label;
}

void setLabelText(Label* label, const char* text){
    
    label->text = (char*)realloc(label->text, sizeof(char)*(strlen(text)+1));
    strcpy(label->text, text);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, label->text, C_GREEN);
    if(ISNULL(textSurface)){
        printf("nao foi possivel setar valor de label\n");
        return;
    }
    
    SDL_DestroyTexture(label->texture_text);
    label->texture_text = SDL_CreateTextureFromSurface(renderer, textSurface);    
    SDL_FreeSurface(textSurface);
    
}

void renderLabel(Label* label){

    SDL_RenderCopy(renderer, label->texture_text, NULL, label->rect_text);

}