#ifndef MAPBIG_H
#define MAPBIG_H

#include <SDL/SDL.h>
#include "../D2SDL/D2SDLscreen.h"
#include "../D2SDL/D2SDLmap.h"

class mapBig : public D2SDLmap
{
    public:
        mapBig();
        virtual ~mapBig();
    protected:
        SDL_Surface* screen();
    private:
        SDL_Surface* game_screen;
};

#endif // MAPBIG_H
