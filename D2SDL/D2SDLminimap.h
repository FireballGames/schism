/* 
 * File:   D2SDLminimap.h
 * Author: d2emon
 *
 * Created on 25 Январь 2014 г., 0:34
 */

#ifndef D2SDLMINIMAP_H
#define	D2SDLMINIMAP_H

#include <SDL/SDL.h>
#include "D2SDLimage.h"

class D2SDLminimap {
public:
    SDL_Rect clip[4][8];
    SDL_Rect clipBig[4][8];
    SDL_Surface* image;
    D2SDLimage* terrain;
    D2SDLimage* terrain_small;
    
    D2SDLminimap();
    D2SDLminimap(const D2SDLminimap& orig);
    virtual ~D2SDLminimap();

    int initialize();
    int finalize();
    int fill(int x, int y, int id, SDL_Rect* clip);
    int fillBig(int x, int y, int id, SDL_Surface* screen, SDL_Rect* clip);
    int show(int x, int y, SDL_Surface* screen);
private:

};

#endif	/* D2SDLMINIMAP_H */

