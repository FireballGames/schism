#include "screenLogoSDL.h"

const char* SDL_LOGO_FILENAME = "images/logo_sdl.bmp";

screenLogoSDL::screenLogoSDL(D2SDLgraph* graph){
    this->graph = graph;

    delay         = 2000;
    show_cursor   = 0;

    loadImage(SDL_LOGO_FILENAME);
}

screenLogoSDL::~screenLogoSDL(){
    //dtor
}
