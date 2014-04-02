#include "D2SDLcomponent.h"

D2SDLcomponent::D2SDLcomponent()
{
    parent = NULL;
    next   = NULL;
}

D2SDLcomponent::~D2SDLcomponent()
{
    if(next)    delete next;
}
