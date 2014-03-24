#include "screenLogoSDL.h"

const char* SDL_LOGO_FILENAME = "images/logo_sdl.bmp";

screenLogoSDL::screenLogoSDL()
{
    logo_filename = new char[sizeof(SDL_LOGO_FILENAME)];
    strcpy(logo_filename, SDL_LOGO_FILENAME);
    delay         = 2000;
    show_cursor   = 0;
}

screenLogoSDL::~screenLogoSDL()
{
    //dtor
}
