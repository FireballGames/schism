#include "D2SDLcomponent.h"

D2SDLcomponent::D2SDLcomponent()
{
    //ctor
}

D2SDLcomponent::~D2SDLcomponent()
{
    if(next) delete next;//dtor
}
