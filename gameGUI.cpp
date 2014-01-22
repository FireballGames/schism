/* 
 * File:   gameGUI.cpp
 * Author: d2emon
 * 
 * Created on 22 Январь 2014 г., 23:02
 */

#include "gameGUI.h"
#include "SDLgraph.h"

const int   LOGO_FIREBALL_X = 0;
const int   LOGO_FIREBALL_Y = 0;
const char* LOGO_FIREBALL   = "images/logo_fireball.bmp";
const int   DELAY_FIREBALL  = 2000;

const int   LOGO_SDL_X = 0;
const int   LOGO_SDL_Y = 0;
const char* LOGO_SDL   = "images/logo_sdl.bmp";
const int   DELAY_SDL  = 2000;

const int   LOGO_SCHISM_X = 0;
const int   LOGO_SCHISM_Y = 0;
const char* LOGO_SCHISM   = "images/logo_schism.bmp";
const int   DELAY_SCHISM  = 10000;
    
const int   UNIT_X   = 180;
const int   UNIT_Y   = 180;
const char* IMG_UNIT = "images/unit.gif";

const char* IMG_BACKGROUND = "images/background.bmp";

gameGUI::gameGUI() {
    graph = NULL;
}

gameGUI::gameGUI(const gameGUI& orig) {
}

gameGUI::~gameGUI() {
}

int gameGUI::initialize() {
    graph = new SDLgraph;
    return graph->initialize();
}

int gameGUI::title() {
    // Showing logos
    graph->showLogo(LOGO_FIREBALL_X, LOGO_FIREBALL_Y, LOGO_FIREBALL, DELAY_FIREBALL);
    graph->showLogo(LOGO_SDL_X,      LOGO_SDL_Y,      LOGO_SDL,      DELAY_SDL     );
    graph->showLogo(LOGO_SCHISM_X,   LOGO_SCHISM_Y,   LOGO_SCHISM,   DELAY_SCHISM  );
    
    return 0;
}

int gameGUI::mainLoop() {
    bool quit = false;
    
    // Showing main screen
    graph->showImage(   0,   0, IMG_BACKGROUND);
    graph->showImage( 180, 140, IMG_UNIT      );
    if(graph->flip() < 0)
    {
        return -1;
    }
    
    while(!quit)
    {
        while(graph->pollEvent()) {
            if(graph->event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
    
    return 0;
}

int gameGUI::finalize() {
    return graph->finalize();
}