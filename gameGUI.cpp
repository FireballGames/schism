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
const char* IMG_USERLOC    = "images/terrain/userloc.png";

const int max_x = 255;
const int max_y = 255;

gameGUI::gameGUI() {
    graph = NULL;
    m = new map;
    x = 50;
    y = 50;
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

    return errorcode;
}

int gameGUI::title() {
    graph->showLogo(LOGO_FIREBALL, DELAY_FIREBALL);
    graph->showLogo(LOGO_SDL,      DELAY_SDL     );
    graph->showLogo(LOGO_SCHISM,   DELAY_SCHISM  );

    m->generate();

    return 0;
}

int gameGUI::showmap() {
    int dx = 4;
    int dy = 4;

    for(int i=0; i<(max_x/dx); i++) {
        for(int j=0; j<(max_y/dy); j++) {
            location* loc = NULL;
            loc = m->locations[i*dx][j*dy];
            graph->minimap->fill(i, j, loc->loctype, &graph->minimap->clip[loc->loctype][loc->style]);
        }
    }
    int sx = x/dx;
    int sy = y/dy;
    int sx1 = (2 * (sx - sy) ) + 128 + 5;
    int sy1 = sy + sx + 40;

    graph->fillImage(graph->minimap->image, sx1, sy1, IMG_USERLOC);
    // graph->minimap->show(528, 0, graph->screen);

    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            location* loc = NULL;
            int lx = i + x - 10;
            int ly = j + y - 10;
            if((lx>=0)&&(ly>=0)) {
                loc = m->locations[lx][ly];
                int px = (100 * (i - j) )/2 + 350;
                int py = (50  * (j + i) )/2 - 200;
                graph->minimap->fillBig(px, py, loc->loctype, graph->screen, &graph->minimap->clipBig[loc->loctype][loc->style]);
            }
        }
    }

    graph->fillImage(graph->screen, 350, 200, IMG_UNIT      );
    graph->minimap->show(528, 0, graph->screen);

    if(graph->flip() < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

int gameGUI::mainLoop() {
    bool quit = false;

    // Showing main screen
    graph->fillImage(graph->screen,   0,   0, IMG_BACKGROUND);

    showmap();

    while(!quit)
    {
        while(graph->pollEvent()) {
            if(graph->event.type == SDL_KEYDOWN) {
                //Выбрать правильное сообщение
                switch( graph->event.key.keysym.sym ) {
                    case SDLK_UP:    if(y>0)     {y--; printf("%d, %d\n", x, y); showmap();} break;
                    case SDLK_DOWN:  if(y<max_y) {y++; printf("%d, %d\n", x, y); showmap();} break;
                    case SDLK_LEFT:  if(x>0)     {x--; printf("%d, %d\n", x, y); showmap();} break;
                    case SDLK_RIGHT: if(x<max_x) {x++; printf("%d, %d\n", x, y); showmap();} break;
                    default: break;
                }
            }
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
