#ifndef MAPMINI_H
#define MAPMINI_H

#include "../D2SDL/D2SDLmap.h"

class mapMini : public D2SDLmap
{
    public:
        mapMini();
        virtual ~mapMini();

        int setViewpoint(int x, int y);
        int initialize();
    protected:
        SDL_Surface* screen();
    private:
};

#endif // MAPMINI_H
