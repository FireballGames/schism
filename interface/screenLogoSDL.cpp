#include "screenLogoSDL.h"

const char* SDL_LOGO_FILENAME = "images/logo_sdl.bmp";

screenLogoSDL::screenLogoSDL(){
    delay         = 2000;
    show_cursor   = 0;

    loadImage(SDL_LOGO_FILENAME);
}

screenLogoSDL::~screenLogoSDL(){
    //dtor
}

int screenLogoSDL::on_loop(D2SDLgraph* graph) {
    int show = true;

    while(graph->pollEvent()) {
        if(graph->event.type == SDL_MOUSEBUTTONDOWN) {
            show = (graph->event.button.button != SDL_BUTTON_LEFT);
        }
        if(graph->event.type == SDL_KEYDOWN) {
            show = false;
        }
    }

    if(timer->get_ticks() >= delay) {
        show = false;
    }

    return show;
}
