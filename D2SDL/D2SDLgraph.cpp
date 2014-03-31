/*
 * File:   SDLgraph.cpp
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#include "D2SDLgraph.h"
#include "D2SDLimage.h"
#include "D2SDLminimap.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdlib>

const int SCREEN_WIDTH_LOW   =  800;
const int SCREEN_HEIGHT_LOW  =  600;
const int SCREEN_WIDTH_HIGH  = 1200;
const int SCREEN_HEIGHT_HIGH =  900;

const int SCREEN_BPP    = 32;

const int SCREEN_MODE_WINDOW     = SDL_SWSURFACE;
const int SCREEN_MODE_FULLSCREEN = SDL_FULLSCREEN;

const char* WM_CAPTION  = "Схизма";

D2SDLgraph::D2SDLgraph() {
    screen  = NULL;
}

D2SDLgraph::D2SDLgraph(const D2SDLgraph& orig) {
}

D2SDLgraph::~D2SDLgraph() {
}

/**
 * Initializing SDL
 * @return initialized
 */
int D2SDLgraph::initialize(int windowed = 0, int highres = 0) {
    quit = 0;

    printf("SDL initialization\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    int mode = SCREEN_MODE_FULLSCREEN;
    if(windowed)
    {
        mode = SCREEN_MODE_WINDOW;
    }

    int w = SCREEN_WIDTH_LOW;
    int h = SCREEN_HEIGHT_LOW;
    if(highres)
    {
        w = SCREEN_WIDTH_HIGH;
        h = SCREEN_HEIGHT_HIGH;
    }

    screen = SDL_SetVideoMode(w, h, SCREEN_BPP, mode);
    if(!screen)
    {
        return -2;
    }

    SDL_WM_SetCaption(WM_CAPTION, NULL);

    return 0;
}

/**
 * Finalization SDL
 * @return finalized
 */
int D2SDLgraph::finalize() {
    printf("SDL finalization\n");
    SDL_Quit();
    return 0;
}

char* D2SDLgraph::getError() {
    return SDL_GetError();
}

/**
 * Filling image
 * @param x horizontal position
 * @param y vertical position
 * @param filename filename of the image
 * @return errorcode
 */
int D2SDLgraph::fillImage(SDL_Surface* dest, int x, int y, const char* filename, int color_key)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    D2SDLimage* src = NULL;

    src = new D2SDLimage(filename, 0);
    SDL_BlitSurface(src->image, NULL, dest, &offset);
    src->free();

    return 0;
}

int D2SDLgraph::flip()
{
    return SDL_Flip(screen);
}

int D2SDLgraph::pollEvent()
{
    int res = SDL_PollEvent(&event);

    if(res){
        if(event.type == SDL_QUIT) {
            quit = 1;
        }
    }

    return res;
}
