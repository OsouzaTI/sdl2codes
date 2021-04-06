#include "gui.h"

void GUI_Button(int x, int y){
    
    SDL_Rect bt = { x, y, 100, 50 };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255 );
    SDL_RenderDrawRect(renderer, &bt);

}

void GUI_InputText(void(*cb_func)(lNode*, vNode*), lNode* l, char* v, int x, int y){
        
    SDL_Rect in = { x, y, 150, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
    SDL_RenderDrawRect(renderer, &in);

    Text* input = createLabel(v);
    renderLabel(input, x+50, y+10, 10 * strlen(v) + 10, 20);
    
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if(MOUSE(mx, my, x, y, 150, 50)){

        /* hover do botao */
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255 );
        SDL_RenderDrawRect(renderer, &in);

        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_TEXTINPUT:{
                if(strlen(v) < MAX_INPUT_STRING-1){
                    strcat(v, event.text.text);
                }
                printf("%s\n", v);
            } break;
            case SDL_KEYDOWN:{
                if(event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER){
                    vNode* no = createVisualNode(rand()%10, rand()%10, atoi(v));
                    cb_func(l, no);
                    strcpy(v, "");
                }else if(event.key.keysym.sym == SDLK_BACKSPACE){
                    printf("sub string\n");
                    int length = strlen(v);
                    /* apaga o ultimo caractere da string */
                    *((v + length) - 1) = '\0';
                }
            }break;
            case SDL_MOUSEBUTTONDOWN:{
            }break;
            default:{
                
            } break;
        }
        event.type = -1;

    }

    destroyLabel(input);

}