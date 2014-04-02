#include "D2SDLcomponent.h"

D2SDLcomponent::D2SDLcomponent()
{
    //ctor
}

D2SDLcomponent::~D2SDLcomponent()
{
    printf("Deleting next\n");
    if(next) delete next;//dtor
}
