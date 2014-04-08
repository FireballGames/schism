#include "screenLogoSchism.h"

const char* SCHISM_LOGO_FILENAME = "images/logo_schism.bmp";

const char* SCHISM_BTN_NEWGAME = "images/buttons/new_game.png";
const char* SCHISM_BTN_OPTIONS = "images/buttons/options.png";
const char* SCHISM_BTN_EXIT    = "images/buttons/exit.png";

void newgame_mouseUp(D2SDLcomponent* sender, SDL_Event event)
{
    D2SDLscreen* logo = dynamic_cast<D2SDLscreen*>(sender->parent);
    if(logo)
        logo->showing = false;
}

void options_mouseUp(D2SDLcomponent* sender, SDL_Event event)
{
    D2SDLpanel* logo = dynamic_cast<D2SDLpanel*>(sender);
    if(logo)
        logo->graph->stopped = true;
}

void exit_mouseUp(D2SDLcomponent* sender, SDL_Event event)
{
    D2SDLpanel* logo = dynamic_cast<D2SDLpanel*>(sender);
    if(logo)
        logo->graph->stopped = true;
}

/*
void schism_keyDown(D2SDLcomponent* sender, SDL_Event event) {
    D2SDLscreen* logo = dynamic_cast<D2SDLscreen*>(sender);
    if(logo)
        logo->showing = false;
}
*/

screenLogoSchism::screenLogoSchism(D2SDLgraph* graph) {
    show_cursor = 0;

    setGraph(graph);

    loadBackground(SCHISM_LOGO_FILENAME);

    //on_keyDown = schism_keyDown;

    D2SDLpanel* p1 = addButton(8,   8, SCHISM_BTN_NEWGAME);
    D2SDLpanel* p2 = addButton(8,  64, SCHISM_BTN_OPTIONS);
    D2SDLpanel* p3 = addButton(8, 128, SCHISM_BTN_EXIT   );

    p1->on_mouseButtonUp = newgame_mouseUp;
    p2->on_mouseButtonUp = options_mouseUp;
    p3->on_mouseButtonUp = exit_mouseUp;
}

screenLogoSchism::~screenLogoSchism(){
    //dtor
}

D2SDLpanel* screenLogoSchism::addButton(int x, int y, const char* filename)
{
    D2SDLpanel* c = (D2SDLpanel*) children;

    D2SDLpanel* p   = new D2SDLpanel();
    p->loadGraph(graph);
    p->init(10, 10, true);
    p->loadImage(filename);
    p->surface->x = c->surface->x + x;
    p->surface->y = c->surface->y + y;
    //printf("Newbutton %d, %d, %d, %d\n", p->surface->x, p->surface->y, p->surface->width, p->surface->height);
    add_child(p);

    return p;
}
