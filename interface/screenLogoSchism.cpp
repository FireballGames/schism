#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

screenLogoSchism::screenLogoSchism()
{
    logo_filename = SCHISM_LOGO_FILENAME;
    delay         = 10000;
    show_cursor   = 0;
    cursor        = new D2SDLimage("images/cursor.png", 1);
}

screenLogoSchism::~screenLogoSchism()
{
    //dtor
}
