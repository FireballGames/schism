#ifndef D2SDLIMAGE_H
#define D2SDLIMAGE_H

#include "D2SDLsurface.h"


class D2SDLimage : public D2SDLsurface
{
    public:
        D2SDLimage();
        virtual ~D2SDLimage();
        SDL_Surface* load(const char* filename, int color_key = 1);
    protected:
    private:
};

#endif // D2SDLIMAGE_H
