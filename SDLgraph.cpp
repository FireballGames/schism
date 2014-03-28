/*
 * File:   SDLgraph.cpp
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#include "SDLgraph.h"
#include "D2SDL/D2SDLimage.h"
#include "D2SDL/D2SDLminimap.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdlib>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP    = 32;

const char* WM_CAPTION  = "Схизма";

SDLgraph::SDLgraph() {
    screen  = NULL;
    // minimap = NULL;
}

SDLgraph::SDLgraph(const SDLgraph& orig) {
}

SDLgraph::~SDLgraph() {
}

/**
 * Initializing SDL
 * @return initialized
 */
int SDLgraph::initialize() {
    printf("SDL initialization\n");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //SDL_FULLSCREEN
    if(!screen)
    {
        return -2;
    }

    /*
    minimap = new D2SDLminimap;
    if(minimap->initialize() < 0)
    {
        return -2;
    }
    */

    SDL_WM_SetCaption(WM_CAPTION, NULL);

    return 0;
}

/**
 * Finalization SDL
 * @return finalized
 */
int SDLgraph::finalize() {
    printf("SDL finalization\n");
    //minimap->finalize();
    SDL_Quit();
    return 0;
}

char* SDLgraph::getError() {
    return SDL_GetError();
}

/**
 * Filling image
 * @param x horizontal position
 * @param y vertical position
 * @param filename filename of the image
 * @return errorcode
 */
int SDLgraph::fillImage(SDL_Surface* dest, int x, int y, const char* filename, int color_key)
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

/**
 * Showing  logo
 * @param screen screen surface
 * @param x horizontal position
 * @param y vertical position
 * @param filename image filename
 * @param delay time to show logo
 * @return errorcode
 */
int SDLgraph::showLogo(const char* filename, const int delay)
{
    fillImage(screen, 0, 0, filename);
    int res = flip();
    SDL_Delay(delay);
    return res;
}

int SDLgraph::flip()
{
    return SDL_Flip(screen);
}

int SDLgraph::pollEvent()
{
    SDL_PollEvent(&event);

    return 0;
}
