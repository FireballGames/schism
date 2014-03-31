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
    image = new D2SDLimage(filename, 1);
    //ctor
}

void D2SDLcursor::getPosition()
{
    SDL_GetMouseState(&x, &y);
}


