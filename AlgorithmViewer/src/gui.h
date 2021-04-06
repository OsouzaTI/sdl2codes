#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "structure.h"
#include "label.h"

#define MOUSE(mx, my, x, y, w, h) (mx >= x && mx < (x+w))&&(my >= y && my < (y+h))
#define MAX_INPUT_STRING 4

void GUI_Button(int x, int y);
void GUI_InputText(void(*cb_func)(lNode*, vNode*),lNode* l, char* v, int x, int y);

#endif