/* 
 * File:   D2SDLimage.h
 * Author: d2emon
 *
 * Created on 25 Январь 2014 г., 0:03
 */

#ifndef D2SDLIMAGE_H
#define	D2SDLIMAGE_H

#include <SDL/SDL.h>

class D2SDLimage {
public:
    SDL_Surface* image;
    D2SDLimage(const char* filename);
    D2SDLimage(const D2SDLimage& orig);
    virtual ~D2SDLimage();
    SDL_Surface* load(const char* filename);
    int free();
private:

};

#endif	/* D2SDLIMAGE_H */

