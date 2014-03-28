/*
 * File:   SDLgraph.h
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#ifndef SDLGRAPH_H
#define	SDLGRAPH_H

#include "D2SDLimage.h"
#include "D2SDLminimap.h"

#include <SDL/SDL.h>

class D2SDLgraph {
public:
    SDL_Surface* screen;
    D2SDLminimap* minimap;
    SDL_Event event;

    int quit;

    D2SDLgraph();
    D2SDLgraph(const D2SDLgraph& orig);
    virtual ~D2SDLgraph();

    int initialize();
    int finalize();
    int fillImage(SDL_Surface* dest, int x, int y, const char* filename, int color_key = 1);
    int showLogo(const char* filename, const int delay);
    int flip();
    int pollEvent();
    char* getError();
    SDL_Rect buildrect(int x, int y);
private:
};

#endif	/* SDLGRAPH_H */

