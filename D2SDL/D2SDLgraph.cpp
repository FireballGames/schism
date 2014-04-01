/*
 * File:   SDLgraph.cpp
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "D2SDLgraph.h"
#include "D2SDLimage_old.h"
#include "D2SDLminimap.h"

const int SCREEN_WIDTH_LOW   =  800;
const int SCREEN_HEIGHT_LOW  =  600;
const int SCREEN_WIDTH_HIGH  = 1024;
const int SCREEN_HEIGHT_HIGH =  768;

const int SCREEN_BPP    = 32;

const int SCREEN_MODE_WINDOW     = SDL_SWSURFACE;
const int SCREEN_MODE_FULLSCREEN = SDL_FULLSCREEN;

const char* WM_CAPTION  = "Схизма";

const int ERROR_SDL_INIT     = -1;
const int ERROR_SDL_SET_MODE = -2;



D2SDLgraph::D2SDLgraph()
{
    surface  = NULL;

    width  = SCREEN_WIDTH_LOW;
    height = SCREEN_HEIGHT_LOW;

    stopped = false;
}

D2SDLgraph::~D2SDLgraph()
{
    //
}

/**
 * Initializing SDL
 * @param fullscreen int If to show in fullscreen
 * @param highres int If to show in high resolution
 * @return initialized
 */
int D2SDLgraph::initialize(bool fullscreen = false, bool highres = false)
{
    printf("SDL initialization\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return ERROR_SDL_INIT;

    int mode = (fullscreen) ? SCREEN_MODE_FULLSCREEN : SCREEN_MODE_WINDOW;

    if(highres) width  = SCREEN_WIDTH_HIGH;
    if(highres) height = SCREEN_HEIGHT_HIGH;

    surface = SDL_SetVideoMode(width, height, SCREEN_BPP, mode);
    if(!surface) return -2;

    SDL_WM_SetCaption(WM_CAPTION, NULL);

    return 0;
}

/**
 * Finalization SDL
 * @return finalized
 */
int D2SDLgraph::finalize()
{
    printf("SDL finalization\n");
    SDL_Quit();
    return 0;
}

/**
 * Gettng SDL error
 * @return char Error text
 */
char* D2SDLgraph::getError()
{
    return SDL_GetError();
}

/**
 * Polling events
 * @return polled
 */
int D2SDLgraph::pollEvent()
{
    int polled = SDL_PollEvent(&event);

    if(polled){
        if(event.type == SDL_QUIT) {
            stopped = true;
        }
    }

    return polled;
}

/**
 * Flipping surface
 * @return errorcode
 */
int D2SDLgraph::flip()
{
    return SDL_Flip(surface);
}

/**
 * Filling image
 * @param x horizontal position
 * @param y vertical position
 * @param filename filename of the image
 * @param color_key int To make transparent
 * @return errorcode
 */
int D2SDLgraph::fillImage(SDL_Surface* dest, int x, int y, const char* filename, int color_key)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    D2SDLimage_old* src = new D2SDLimage_old(filename, 0);
    SDL_BlitSurface(src->image, NULL, dest, &offset);
    src->free();

    return 0;
}
