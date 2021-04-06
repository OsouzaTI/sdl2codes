#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define FPS 10
#define FRAME_TARGET_TIME (1000/FPS)

extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern TTF_Font     *font;
extern TTF_Font     *hud;
extern SDL_Event    event;
/* Sounds effects */
extern Mix_Chunk *fx_yamete;

#define  WINDOW_WIDTH 1000
#define  WINDOW_HEIGHT 800

// initialization the window
int InitializeWindow(void);


#endif