#ifndef D2SDLCOMPONENT_H
#define D2SDLCOMPONENT_H

#include "D2SDLsurface.h"

class D2SDLcomponent
{
    public:
        D2SDLcomponent();
        virtual ~D2SDLcomponent();

        char* name;

        D2SDLcomponent* parent;  // Parent panel
        D2SDLcomponent* next;    // Next panel
    protected:
    private:
};

#endif // D2SDLCOMPONENT_H
