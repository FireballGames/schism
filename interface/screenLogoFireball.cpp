#include "screenLogoFireball.h"

#include <SDL/SDL.h>

const char* FIREBALL_LOGO_FILENAME = "images/logo_fireball.bmp";

screenLogoFireball::screenLogoFireball() {
    delay         = 2000;
    show_cursor   = 0;

    loadImage(FIREBALL_LOGO_FILENAME);
}

screenLogoFireball::~screenLogoFireball() {
    //dtor
}

int screenLogoFireball::on_loop(D2SDLgraph* graph) {
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

