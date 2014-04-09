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
        unsigned int water_modifier;
        SDL_Rect getClip(location* loc);
    private:
        SDL_Surface* game_screen;
        D2SDLtimer* timer_water;
};

#endif // MAPBIG_H
