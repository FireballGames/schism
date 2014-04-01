#ifndef D2SDLSURFACE_H
#define D2SDLSURFACE_H

#include <SDL/SDL.h>

#include "D2SDLgraph.h"

class D2SDLsurface
{
    public:
        D2SDLsurface();
        virtual ~D2SDLsurface();

        SDL_Surface* surface; // Surface

        int init(int w, int h);
        int paint(D2SDLgraph* graph);
    protected:
    private:
};

#endif // D2SDLSURFACE_H
