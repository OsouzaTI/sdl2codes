#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "structure.h"
#include "label.h"
#include "gui.h"

int frameTargetTime = 60;
int previousFrameTime = 0;
int isRuning = 0;

Mouse mouse;
Text* label1;
Text* label2;

char entrada[MAX_INPUT_STRING];
char entrada2[MAX_INPUT_STRING];

#define SIZE_NODES 0
lNode* lista;

void setup(){

    /* Permitir entrada de texto */
    SDL_StartTextInput();

    label1 = createLabel("Adicionar no inicio");
    label2 = createLabel("Adicionar no final");

    lista = createLNode();
    int i;
    for(i = 0; i < SIZE_NODES; i++){
        vNode* n = createVisualNode(
            50 * i + 10,
            50 * i + 50,
            rand()%10
        );
        insertAtBegin(lista, n);
    }

}

void processInput(){
    
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRuning = 0;
            break;
    }

}

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), previousFrameTime + frameTargetTime));
    SDL_GetMouseState(&mouse.x, &mouse.y);
    moveVisualNode(&mouse, lista);
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* renderizando um nodo qualquer */
    linkVisualNode(lista);
    renderVisualNode(lista);
    renderVisualNodeText(lista);

    renderLabel(label1, WINDOW_WIDTH - 210, 10, 200, 30);
    GUI_InputText(insertAtBegin, lista, entrada,  WINDOW_WIDTH - 210, 40);

    renderLabel(label2, WINDOW_WIDTH - 210, 100, 200, 30);
    GUI_InputText(insertAtEnd, lista, entrada2,  WINDOW_WIDTH - 210, 130);


    SDL_RenderPresent(renderer);

}

int main(int argc, char *argv[]){
    isRuning = InitializeWindow();
    printf("hello SDL2\n");    
    setup();
    while(isRuning){
        processInput();
        update();
        render();
    }
    cleanLNode(lista);
    return 0;
}