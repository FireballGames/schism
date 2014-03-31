#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

screenLogoSchism::screenLogoSchism() {
    show_cursor   = 0;

    loadImage(SCHISM_LOGO_FILENAME);
}

screenLogoSchism::~screenLogoSchism(){
    //dtor
}

int screenLogoSchism::on_loop(D2SDLgraph* graph) {
    int showscreen = true;

    while(graph->pollEvent()) {
        /*
        if(graph->event.type == SDL_MOUSEMOTION) {
            repaint = true;
        }
        */
        if(graph->event.type == SDL_MOUSEBUTTONUP) {
            /*
            cursor->getPosition();

            int mx = cursor->x;
            int my = cursor->y;

            if((mx<200)&&(my<50))
            {
                showscreen = false;
            }
            */

            showscreen = false;
        }
        if(graph->event.type == SDL_KEYDOWN) {
            showscreen = false;
        }

    }

    repaint = true;

    return showscreen;
}
