/*
 * File:   SDLgraph.h
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#ifndef D2SDLGRAPH_H
#define	D2SDLGRAPH_H

#include "D2SDLsurface.h"
//#include "D2SDLimage_old.h"
//#include "D2SDLminimap.h"

#include <SDL/SDL.h>

class D2SDLgraph
{
public:
    D2SDLsurface*  surface; //Drawing surface
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

#endif	/* D2SDLGRAPH_H */

