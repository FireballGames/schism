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
#include <time.h>
#include "interface/screenLogoFireball.h"
#include "interface/screenLogoSDL.h"
#include "interface/screenLogoSchism.h"
#include "interface/screenMain.h"

const int   UNIT_X   = 180;
const int   UNIT_Y   = 180;
const char* IMG_UNIT       = "images/unit.gif";
const char* IMG_CURSOR     = "images/cursor.png";
const char* IMG_BACKGROUND = "images/background.bmp";

const int tile_x = 400; //350
const int tile_y = 256; //200

double moved = 0;

gameGUI::gameGUI() {
    graph  = NULL;
    screen = NULL;
    cursor = NULL;

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

/**
 * Intializing game
 * @return int errorcode 0 if success
 */
int gameGUI::initialize() {
    printf("Game initialization\n");

    int errorcode = 0;

    graph = new SDLgraph;
    errorcode = graph->initialize();
    if(errorcode<0) {
        printf("SDL error: %s\n",  graph->getError());
        return errorcode;
    }

    return errorcode;
}

/**
 * Showing title screen
 * @return int errorcode 0 if success
 */
int gameGUI::title() {
    printf("Showing title screen\n");

    int errorcode = 0;

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

    return errorcode;
}

/**
 * Using main menu screen
 * @return int errorcode 0 if success
 */
int gameGUI::mainmenu() {
    printf("Showing mainmenu\n");

    int errorcode = 0;

    cursor = new D2SDLimage(IMG_CURSOR, 1);

    // Main menu
    screenLogoSchism* logo3 = NULL;
    logo3 = new screenLogoSchism;
    logo3->show(graph);
    delete logo3;

    return errorcode;
}

/**
 * Main game screen
 * @return int errorcode 0 if success
 */
int gameGUI::game() {
    printf("Main game sceen\n");

    int errorcode = 0;

    // Main screen
    screenMain* main_screen = NULL;
    main_screen = new screenMain;
    main_screen->show(graph);

    screen = main_screen->screen;
    //screen = new D2SDLimage(IMG_BACKGROUND);

    moveMouse(0, 0);

    m->generate();
    bigmap->initialize();
    minimap->initialize();


    return errorcode ? errorcode : mainLoop();
}

int gameGUI::showmap() {
    bigmap->generateMap(x, y, m);
    graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    bigmap->show(0, 0, screen->image);

    minimap->generateMap(-1, -1, m);
    minimap->setViewpoint(x,y);
    minimap->show(528, 0, screen->image);

    moveMouse(0, 0);

    if(graph->flip() < 0) {
        moved = 0;
        return -1;
    }
    else {
        moved = time(NULL);
        return 0;
    }
}

int gameGUI::moveView(int dx, int dy) {
    if((dx < 0)&&(x > 0    )) x--;
    if((dx > 0)&&(x < max_x)) x++;
    if((dy < 0)&&(y > 0    )) y--;
    if((dy > 0)&&(y < max_y)) y++;

    showmap();

    return 0;
}

int gameGUI::mainLoop() {
    bool quit = false;

    // Showing main screen
    //graph->fillImage(graph->screen,   0,   0, IMG_BACKGROUND);

    int mx = 400;
    int my = 300;
    showmap();

    while(!quit)
    {
        //if(time(NULL) - moved > 0.01)
        //{
            SDL_GetMouseState(&mx, &my);

            if(mx < 10) {
                moveView(-1,  1);
            }
            if(mx > 790) {
                moveView( 1, -1);
            }
            if(my < 10) {
                moveView(-1, -1);
            }
            if(my > 590) {
                moveView( 1,  1);
            }
        //}

        while(graph->pollEvent()) {
            //printf("%d \n", graph->event.type);
            if(graph->event.type == SDL_MOUSEMOTION) {
                /*
                printf("%d,%d \n", graph->event.motion.x, graph->event.motion.y);
                bigmap->show(0, 0, graph->screen);
                minimap->show(528, 0, graph->screen);
                graph->fillImage(graph->screen, graph->event.motion.x, graph->event.motion.y, IMG_CURSOR);
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

                moveMouse(graph->event.motion.x, graph->event.motion.y);
            }
            if(graph->event.type == SDL_KEYDOWN) {
                switch( graph->event.key.keysym.sym ) {
                    case SDLK_UP:    moveView(-1, -1); break;
                    case SDLK_DOWN:  moveView( 1,  1); break;
                    case SDLK_LEFT:  moveView(-1,  1); break;
                    case SDLK_RIGHT: moveView( 1, -1); break;
                    case SDLK_ESCAPE: quit = true; break;
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

    if(cursor) cursor->free();
    // if(screen) screen->free();
    graph->finalize();

    return 0;
}

void gameGUI::moveMouse(int x=0, int y=0) {
    SDL_BlitSurface(screen->image, NULL, graph->screen, NULL);

    SDL_GetMouseState(&x, &y);

    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(cursor->image,  NULL, graph->screen, &offset);

    graph->flip();
}
