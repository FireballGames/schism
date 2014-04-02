#include "screenLogoFireball.h"

#include <SDL/SDL.h>

const char* FIREBALL_LOGO_FILENAME = "images/logo_fireball.bmp";

screenLogoFireball::screenLogoFireball(D2SDLgraph* graph) {
    setGraph(graph);

    loadBackground(FIREBALL_LOGO_FILENAME);
}

screenLogoFireball::~screenLogoFireball() {
    //dtor
}
