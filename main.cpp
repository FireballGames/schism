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

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Surface* hello  = NULL;
    SDL_Surface* screen = NULL;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
    hello  = SDL_LoadBMP("images/ready/logo_fireball.bmp");
    
    SDL_BlitSurface(hello, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(2000);
    
    SDL_FreeSurface(hello);
    SDL_Quit();
    
    return 0;
}

