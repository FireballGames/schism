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

class D2SDLgraph
{
public:
    SDL_Surface*  surface; //Drawing surface
    //D2SDLminimap* minimap;
    SDL_Event event; // Polled event

    int width;    // Window width
    int height;   // Window height
    bool stopped; // If game is stopping

    D2SDLgraph();
    virtual ~D2SDLgraph();

    int initialize(bool fullscreen, bool highres);
    int finalize();
    char* getError();
    int pollEvent();
    int flip();
    int fillImage(SDL_Surface* dest, int x, int y, const char* filename, int color_key = 1);
    //int showLogo(const char* filename, const int delay);
    //SDL_Rect buildrect(int x, int y);
private:
};

#endif	/* SDLGRAPH_H */

