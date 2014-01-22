/* 
 * File:   SDLgraph.cpp
 * Author: d2emon
 * 
 * Created on 22 Январь 2014 г., 22:28
 */

#include "SDLgraph.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP    = 32;

const char* WM_CAPTION  = "Схизма";

SDLgraph::SDLgraph() {
    screen = NULL;
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
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL init error: %s",  SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(!screen)
    {
        printf("SDL mode error: %s",  SDL_GetError());
        return -2;
    }
    SDL_WM_SetCaption(WM_CAPTION, NULL);
    
    return 0;
}

/**
 * Finalization SDL
 * @return finalized
 */
int SDLgraph::finalize() {
    SDL_Quit();
    return 0;
}

/**
 * Loading image into SDL
 * @param filename image file
 * @return optimized image
 */
SDL_Surface* SDLgraph::loadImage(const char* filename)
{
    SDL_Surface* loaded_image    = NULL;
    SDL_Surface* optimized_image = NULL;
    
    loaded_image = IMG_Load(filename);
    if(loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormat(loaded_image);
        SDL_FreeSurface(loaded_image);
    }
    
    return optimized_image;
}

/**
 * Showing image
 * @param x horizontal position
 * @param y vertical position
 * @param filename filename of the image
 * @return errorcode
 */
int SDLgraph::showImage(int x, int y, const char* filename)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
 
    SDL_Surface* logo = NULL;
 
    logo = loadImage(filename);
    SDL_BlitSurface(logo, NULL, screen, &offset);
    SDL_FreeSurface(logo);

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
int SDLgraph::showLogo(int x, int y, const char* filename, const int delay)
{
    showImage(x, y, filename);
    return flip();   
}

int SDLgraph::flip()
{
    return SDL_Flip(screen);
}

int SDLgraph::pollEvent()
{
    SDL_PollEvent(&event);
}