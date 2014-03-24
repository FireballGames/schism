#include "screenLogoFireball.h"

const char* FIREBALL_LOGO_FILENAME = "images/logo_fireball.bmp";

screenLogoFireball::screenLogoFireball()
{
    logo_filename = new char[sizeof(FIREBALL_LOGO_FILENAME)];
    strcpy(logo_filename, FIREBALL_LOGO_FILENAME);
    delay         = 2000;
    show_cursor   = 0;
}

screenLogoFireball::~screenLogoFireball()
{
    //dtor
}
