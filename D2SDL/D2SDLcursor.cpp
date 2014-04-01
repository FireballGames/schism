#include "D2SDLcursor.h"

D2SDLcursor::D2SDLcursor()
{
    image = NULL;
    //ctor
}

D2SDLcursor::~D2SDLcursor()
{
    //dtor
}

int D2SDLcursor::load(const char* filename)
{
    image = new D2SDLimage_old(filename, 1);

    return 0;
}

void D2SDLcursor::getPosition()
{
    SDL_GetMouseState(&x, &y);
}


