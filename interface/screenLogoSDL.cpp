#include "screenLogoSDL.h"

const char* SDL_LOGO_FILENAME = "images/logo_sdl.bmp";

screenLogoSDL::screenLogoSDL(D2SDLgraph* graph){
    setGraph(graph);

    loadBackground(SDL_LOGO_FILENAME);
}

screenLogoSDL::~screenLogoSDL(){
    //dtor
}
