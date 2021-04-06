#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Surface  *windowSurface;
extern TTF_Font     *font;
extern TTF_Font     *hud;
extern SDL_Event    event;
extern float        deltaTime;
extern int          WINDOW_WIDTH;
extern int          WINDOW_HEIGHT;

/* Sounds effects */
extern Mix_Chunk *fx_shot;
extern Mix_Chunk *fx_spaceKilled;

// initialization the window
int InitializeWindow(void);


#endif