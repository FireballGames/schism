#ifndef D2SDLSURFACE_H
#define D2SDLSURFACE_H

#include <SDL/SDL.h>

//#include "D2SDLgraph.h"

class D2SDLsurface
{
    public:
        D2SDLsurface();
        virtual ~D2SDLsurface();

        SDL_Surface* surface; // Surface

        int x; // Surface top
        int y; // Surface left
        int width;  // Surface width
        int height; // Surface height

        int init(int w, int h);
        int paint(D2SDLsurface* new_surface);
    protected:
    private:
};

#endif // D2SDLSURFACE_H
