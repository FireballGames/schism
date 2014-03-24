#include "screenMain.h"

const char* MAIN_LOGO_FILENAME = "images/background.bmp";

screenMain::screenMain()
{
    logo_filename = new char[sizeof(MAIN_LOGO_FILENAME)];
    strcpy(logo_filename, MAIN_LOGO_FILENAME);
    delay         = 0;
    show_cursor   = 0;
}

screenMain::~screenMain()
{
    //dtor
}
