#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

screenLogoSchism::screenLogoSchism(D2SDLgraph* graph) {
    setGraph(graph);

    show_cursor   = 0;

    loadImage(SCHISM_LOGO_FILENAME);
}

screenLogoSchism::~screenLogoSchism(){
    //dtor
}

/*
int screenLogoSchism::on_loop() {
    if(graph->event.type == SDL_MOUSEBUTTONUP)
    {
        cursor->getPosition();

        int mx = cursor->x;
        int my = cursor->y;

        if((mx<200)&&(my<50))
        {
            showing = false;
        }
    }
}
*/

void screenLogoSchism::on_mouseButtonDown(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        showing = false;
}

void screenLogoSchism::on_keyDown(SDL_Event event) {
    showing = false;
}
