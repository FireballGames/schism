/* 
 * File:   main.cpp
 * Author: d2emon
 *
 * Created on 20 Январь 2014 г., 22:39
 */

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

using namespace std;

const int delayFireball =  2000;
const int delaySdl      =  2000;
const int delaySchism   = 10000;

const char* logoFireball = "images/logo_fireball.bmp";
const char* logoSdl      = "images/logo_sdl.bmp";
const char* logoSchism   = "images/logo_schism.bmp";

/**
 * Showing  logo
 * @param SDL_Surface* logo logo surface
 * @param SDL_Surface* screen  screen surface
 * @param int delay time to show logo
 */
int showLogo(SDL_Surface* screen,  const char* logo_filename, const int delay)
{
    SDL_Surface* logo = SDL_LoadBMP(logo_filename);

    SDL_BlitSurface(logo, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(delay);

    SDL_FreeSurface(logo);
    
    return 1;   
}

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Surface* screen = NULL;

    // Iitialization SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(800, 600, 0, SDL_SWSURFACE);

    // Showing logos
    showLogo(screen, logoFireball, delayFireball);
    showLogo(screen, logoSdl,      delaySdl     );
    showLogo(screen, logoSchism,   delaySchism  );

    // Finalization
    SDL_Quit();
    
    return 0;
}