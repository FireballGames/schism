#ifndef D2SDLCOMPONENT_H
#define D2SDLCOMPONENT_H

#include "D2SDLsurface.h"

class D2SDLcomponent
{
    public:
        D2SDLcomponent();
        virtual ~D2SDLcomponent();

        char* name;

        D2SDLcomponent* next; // Next panel
        virtual int paint(D2SDLsurface* new_surface) = 0;
    protected:
    private:
};

#endif // D2SDLCOMPONENT_H
