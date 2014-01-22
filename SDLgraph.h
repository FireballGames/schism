/* 
 * File:   SDLgraph.h
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 22:28
 */

#ifndef SDLGRAPH_H
#define	SDLGRAPH_H

#include <SDL/SDL.h>

class SDLgraph {
public:
    SDL_Surface* screen;
    SDL_Event event;

    SDLgraph();
    SDLgraph(const SDLgraph& orig);
    virtual ~SDLgraph();

    int initialize();
    int finalize();
    SDL_Surface* loadImage(const char* filename);
    int showImage(int x, int y, const char* filename);
    int showLogo(int x, int y, const char* filename, const int delay);
    int flip();
    int pollEvent();
private:
};

#endif	/* SDLGRAPH_H */

