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
#include "interface/screenLogoFireball.h"
#include "interface/screenLogoSDL.h"
#include "interface/screenLogoSchism.h"

const int   UNIT_X   = 180;
const int   UNIT_Y   = 180;
const char* IMG_UNIT       = "images/unit.gif";
const char* IMG_CURSOR     = "images/cursor.png";
const char* IMG_BACKGROUND = "images/background.bmp";

const int tile_x = 400; //350
const int tile_y = 256; //200

gameGUI::gameGUI() {
    graph = NULL;
    m = new map;
    x = 128;
    y = 128;

    bigmap  = new mapBig;
    minimap = new mapMini;
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
    // Fireball logo
    screenLogoFireball* logo1 = NULL;
    logo1 = new screenLogoFireball;
    logo1->show(graph);
    delete logo1;

    // SDL logo
    screenLogoSDL* logo2 = NULL;
    logo2 = new screenLogoSDL;
    logo2->show(graph);
    delete logo2;

    // SDL logo
    screenLogoSchism* logo3 = NULL;
    logo3 = new screenLogoSchism;
    logo3->show(graph);
    delete logo3;

    //graph->showLogo(LOGO_SDL,      DELAY_SDL     );
    //graph->showLogo(LOGO_SCHISM,   DELAY_SCHISM  );

    m->generate();
    bigmap->initialize();
    minimap->initialize();

    return 0;
}

int gameGUI::showmap() {
    /*
    int dx = 5;
    int dy = 5;
    int sx = x/dx;
    int sy = y/dy;
    int sx1 = (2 * (sx - sy) ) + 128 + 5;
    int sy1 = sy + sx + 40;
    */

    /*
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

    */
    // graph->minimap->show(528, 0, graph->screen);

    /*
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            location* loc = NULL;
            int lx = i + x - 10;
            int ly = j + y - 10;
            if((lx>=0)&&(ly>=0)&&(lx<=max_x)&&(ly<=max_y)) {
                loc = m->locations[lx][ly];
                int px = (100 * (i - j) )/2 + tile_x;
                int py = (50  * (j + i) )/2 - tile_y;
                graph->minimap->fillBig(px, py, loc->loctype, graph->screen, &graph->minimap->clipBig[loc->loctype][loc->style]);
            }
        }
    }

    graph->fillImage(graph->screen, tile_x/2, tile_y/2, IMG_UNIT      );
    */
    //graph->minimap->show(528, 0, graph->screen);

    printf("%d, %d\n", x, y);

    bigmap->generateMap(x, y, m);
    graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    bigmap->show(0, 0, graph->screen);

    minimap->generateMap(-1, -1, m);
    minimap->setViewpoint(x,y);
    minimap->show(528, 0, graph->screen);

    /*
    int mx = 0;
    int my = 0;
    SDL_GetMouseState(&mx, &my);
    graph->fillImage(graph->screen, mx, my, IMG_CURSOR);
    SDL_SetCursor(NULL);
    */

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
    //graph->fillImage(graph->screen,   0,   0, IMG_BACKGROUND);

    showmap();

    while(!quit)
    {
        while(graph->pollEvent()) {
            //printf("%d \n", graph->event.type);
            if(graph->event.type == SDL_MOUSEMOTION) {
                /*
                printf("%d,%d \n", graph->event.motion.x, graph->event.motion.y);
                bigmap->show(0, 0, graph->screen);
                minimap->show(528, 0, graph->screen);
                graph->fillImage(graph->screen, graph->event.motion.x, graph->event.motion.y, IMG_CURSOR);
                SDL_SetCursor(NULL);
                if(graph->flip() < 0) {
                    return -1;
                }
                */

                //graph->event.motion.x;
                //graph->event.motion.y;
                //graph->event.motion.xrel;
                //graph->event.motion.yrel;
                //graph->event.motion.state;
                /*
                (SDL_BUTTON(SDL_BUTTON_LEFT))!=0,
                (SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,
                (SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0,
                */
            }
            if(graph->event.type == SDL_KEYDOWN) {
                //Выбрать правильное сообщение
                switch( graph->event.key.keysym.sym ) {
                    case SDLK_UP:    if(y>0)     {y--; showmap();} break;
                    case SDLK_DOWN:  if(y<max_y) {y++; showmap();} break;
                    case SDLK_LEFT:  if(x>0)     {x--; showmap();} break;
                    case SDLK_RIGHT: if(x<max_x) {x++; showmap();} break;
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
