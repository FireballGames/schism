/* 
 * File:   main.cpp
 * Author: d2emon
 *
 * Created on 20 Январь 2014 г., 22:39
 */

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP    = 32;

const int DELAY_FIREBALL =  2000;
const int DELAY_SDL      =  2000;
const int DELAY_SCHISM   = 10000;
const int DELAY_MAIN     = 10000;

const char* WM_CAPTION  = "Схизма";

const char* LOGO_FIREBALL = "images/logo_fireball.bmp";
const char* LOGO_SDL      = "images/logo_sdl.bmp";
const char* LOGO_SCHISM   = "images/logo_schism.bmp";
const char* IMG_UNIT       = "images/unit.gif";
const char* IMG_BACKGROUND = "images/background.bmp";

const int LOGO_FIREBALL_X = 0;
const int LOGO_FIREBALL_Y = 0;
const int LOGO_SDL_X = 0;
const int LOGO_SDL_Y = 0;
const int LOGO_SCHISM_X = 0;
const int LOGO_SCHISM_Y = 0;

const int UNIT_X = 180;
const int UNIT_Y = 180;

SDL_Surface* screen = NULL;
SDL_Event event;

/**
 * Loading image into SDL
 * @param filename image file
 * @return optimized image
 */
SDL_Surface* loadImage(const char* filename)
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
 * @param screen screen surface
 * @param x horizontal position
 * @param y vertical position
 * @param filename filename of the image
 * @return errorcode
 */
int showImage(SDL_Surface* screen, int x, int y, const char* filename)
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
int showLogo(SDL_Surface* screen, int x, int y, const char* filename, const int delay)
{
    showImage(screen, x, y, filename);

    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }

    SDL_Delay(delay);
    //SDL_FreeSurface(logo);
    
    return 0;   
}

/**
 * Initializing SDL
 * @return initialized
 */
int init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(!screen)
    {
        return false;
    }
    SDL_WM_SetCaption(WM_CAPTION, NULL);
    
    return true;
}

/**
 * Finalization SDL
 * @return finalized
 */
int finalize()
{
    SDL_Quit();
    return true;
}

/*
 * 
 */
int main(int argc, char** argv) {
    bool quit = false;
    
    if(!init())
    {
        return  1;
    }
    
    // Showing logos
    showLogo(screen, LOGO_FIREBALL_X, LOGO_FIREBALL_Y, LOGO_FIREBALL, DELAY_FIREBALL);
    showLogo(screen, LOGO_SDL_X,      LOGO_SDL_Y,      LOGO_SDL,      DELAY_SDL     );
    showLogo(screen, LOGO_SCHISM_X,   LOGO_SCHISM_Y,   LOGO_SCHISM,   DELAY_SCHISM  );

    // Showing main screen
    showImage(screen,   0,   0, IMG_BACKGROUND);
    showImage(screen, 180, 140, IMG_UNIT      );
    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit =  true;
            }
        }
    }

    finalize();
    
    return 0;
}