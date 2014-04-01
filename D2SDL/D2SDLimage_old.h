/*
 * File:   D2SDLimage.h
 * Author: d2emon
 *
 * Created on 25 Январь 2014 г., 0:03
 */

#ifndef D2SDLIMAGE_OLD_H
#define	D2SDLIMAGE_OLD_H

#include <SDL/SDL.h>

//#include "D2SDLsurface.h"

class D2SDLimage_old //: public D2SDLsurface
{
public:
    SDL_Surface* image;
    D2SDLimage_old(const char* filename, int color_key = 1);
    virtual ~D2SDLimage_old();
    SDL_Surface* load(const char* filename, int color_key = 1);
    int free();
private:

};

#endif	/* D2SDLIMAGE_H */

