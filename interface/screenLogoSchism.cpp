#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

screenLogoSchism::screenLogoSchism() {
    show_cursor   = 1000;

    loadImage(SCHISM_LOGO_FILENAME);
    cursor        = new D2SDLimage("images/cursor.png", 1);
}

screenLogoSchism::~screenLogoSchism(){
    //dtor
}

int screenLogoSchism::on_loop(D2SDLgraph* graph) {
    int show = true;

    while(graph->pollEvent()) {
        if(graph->event.type == SDL_MOUSEBUTTONUP) {
            printf("%d\n", graph->event.button);
            show = false; //(graph->event.button == SDL_BUTTON_LEFT);
        }
    }

    if(timer->get_ticks() >= delay) {
        show = false;
    }

    return show;
}
