#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern TTF_Font     *font;
extern TTF_Font     *hud;
extern SDL_Event    event;
extern int  WINDOW_WIDTH;
extern int  WINDOW_HEIGHT;

// initialization the window
int InitializeWindow(void);


#endif