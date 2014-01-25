/* 
 * File:   gameGUI.cpp
 * Author: d2emon
 * 
 * Created on 22 Январь 2014 г., 23:02
 */

#include "gameGUI.h"
#include "SDLgraph.h"
#include "map.h"
#include <cstdlib>

const char* LOGO_FIREBALL   = "images/logo_fireball.bmp";
const int   DELAY_FIREBALL  = 2000;

const char* LOGO_SDL   = "images/logo_sdl.bmp";
const int   DELAY_SDL  = 2000;

const char* LOGO_SCHISM   = "images/logo_schism.bmp";
const int   DELAY_SCHISM  = 10000;
    
const int   UNIT_X   = 180;
const int   UNIT_Y   = 180;
const char* IMG_UNIT = "images/unit.gif";

const char* IMG_BACKGROUND = "images/background.bmp";

gameGUI::gameGUI() {
    graph = NULL;
    m = new map;
}

gameGUI::gameGUI(const gameGUI& orig) {
}

gameGUI::~gameGUI() {
}

int gameGUI::initialize() {
    printf("Game initialization\n");

    graph = new SDLgraph;
    int errorcode = graph->initialize();

    if(errorcode<0) {
        printf("SDL error: %s\n",  graph->getError());
    }

    for(int i=0; i<50; i++){
        for(int j=0; j<50; j++){
            m->locations[i][j]->loctype = 1;
        }
    }

    return errorcode;
}

int gameGUI::title() {
    graph->showLogo(LOGO_FIREBALL, DELAY_FIREBALL);
    graph->showLogo(LOGO_SDL,      DELAY_SDL     );
    graph->showLogo(LOGO_SCHISM,   DELAY_SCHISM  );
    
    return 0;
}

int gameGUI::mainLoop() {
    bool quit = false;
  
    int x = 256;
    int y = 256;
    int dx = 4;
    int dy = 4;
    
    // Showing main screen
    graph->fillImage(graph->screen,   0,   0, IMG_BACKGROUND);

    for(int i=0; i<(x/dx); i++) {
        for(int j=0; j<(y/dy); j++) {
            location* loc = NULL;
            loc = m->locations[i*dx][j*dy];
            graph->minimap->fill(i, j, loc->loctype, &graph->minimap->clip[loc->loctype][loc->style]);
        }
    }
    // graph->minimap->show(528, 0, graph->screen);

    int ux = 50;
    int uy = 50;
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            location* loc = NULL;
            int lx = i + ux - 10;
            int ly = j + uy - 10;
            if((lx>=0)&&(ly>=0)) {
                loc = m->locations[lx][ly];
                int x = (100 * (i - j) )/2 + 350;
                int y = (50  * (j + i) )/2 - 200;
                graph->minimap->fillBig((int) x, (int) y, loc->loctype, graph->screen, &graph->minimap->clipBig[loc->loctype][loc->style]);
            }
        }
    }

    graph->minimap->show(528, 0, graph->screen);
    graph->fillImage(graph->screen, 350, 200, IMG_UNIT      );
    
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
    printf("Game finalization\n");

    return graph->finalize();
}