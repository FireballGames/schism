#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

const char* SCHISM_BTN_NEWGAME = "images/buttons/new_game.png";

screenLogoSchism::screenLogoSchism(D2SDLgraph* graph) {
    show_cursor = 0;

    setGraph(graph);

    loadBackground(SCHISM_LOGO_FILENAME);

    D2SDLpanel* c = (D2SDLpanel*) children;

    D2SDLpanel* p   = new D2SDLpanel();
    p->loadGraph(graph);
    p->loadImage(SCHISM_BTN_NEWGAME);
    p->surface->x = c->surface->x;
    p->surface->y = c->surface->y;
    printf("Newbutton %d, %d, %d, %d\n", p->surface->x, p->surface->y, p->surface->width, p->surface->height);
    add_child(p);

}

screenLogoSchism::~screenLogoSchism(){
    //dtor
}

/*
int screenLogoSchism::loadImage(const char* filename)
{
    printf("Loading %s\n", filename);

    D2SDLpanel* p   = new D2SDLpanel();
    D2SDLimage* img = new D2SDLimage();
    img->load(filename);

    p->loadGraph(graph);
    p->surface    = img;
    p->surface->x = (graph->width  - p->surface->width )/2;
    p->surface->y = (graph->height - p->surface->height)/2;

    add_child(p);

    loaded = (img != false);

    return loaded ? 0 : -1;
}
*/

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
