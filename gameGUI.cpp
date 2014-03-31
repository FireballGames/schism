/*
 * File:   gameGUI.cpp
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 23:02
 */

#include "map.h"
#include "gameGUI.h"
#include <cstdlib>
#include <time.h>

#include "D2SDL/D2SDLgraph.h"
#include "D2SDL/D2SDLcursor.h"
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
    cursor = NULL;
}

gameGUI::gameGUI(const gameGUI& orig) {
}

gameGUI::~gameGUI() {
}

/**
 * Intializing game
 * @return int errorcode 0 if success
 */
int gameGUI::initialize(int windowed = 0, int highres = 0) {
    printf("Game initialization\n");

    int errorcode = 0;

    graph = new D2SDLgraph;
    errorcode = graph->initialize(windowed, highres);
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

    if(graph->quit)
        return 1;

    // SDL logo
    screenLogoSDL* logo2 = NULL;
    logo2 = new screenLogoSDL;
    logo2->show(graph);
    delete logo2;

    if(graph->quit)
        return 1;

    cursor = new D2SDLcursor;
    cursor->load(IMG_CURSOR);

    return errorcode;
}

/**
 * Using main menu screen
 * @return int errorcode 0 if success
 */
int gameGUI::mainmenu() {
    printf("Showing mainmenu\n");

    int errorcode = 0;

    // Main menu
    screenLogoSchism* logo3 = NULL;
    logo3 = new screenLogoSchism;
    logo3->cursor = cursor;
    logo3->show(graph);
    delete logo3;

    if(graph->quit)
        return 1;

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
    printf("Main Screen initialized\n");
    main_screen->cursor = cursor;
    main_screen->show(graph);

    return errorcode; // ? errorcode : mainLoop();
}

/*
int gameGUI::mainLoop() {
    bool quit = false;

    // Showing main screen
    //graph->fillImage(graph->screen,   0,   0, IMG_BACKGROUND);

    //int mx = 400;
    //int my = 300;
    //showmap();

    while(!quit)
    {
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

        while(graph->pollEvent()) {
            if(graph->event.type == SDL_MOUSEMOTION) {
                printf("%d,%d \n", graph->event.motion.x, graph->event.motion.y);
                bigmap->show(0, 0, graph->screen);
                minimap->show(528, 0, graph->screen);
                graph->fillImage(graph->screen, graph->event.motion.x, graph->event.motion.y, IMG_CURSOR);

                //graph->event.motion.x;
                //graph->event.motion.y;
                //graph->event.motion.xrel;
                //graph->event.motion.yrel;
                //graph->event.motion.state;

                (SDL_BUTTON(SDL_BUTTON_LEFT))!=0,
                (SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,
                (SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0,

                //moveMouse(graph->event.motion.x, graph->event.motion.y);
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
*/

int gameGUI::finalize() {
    printf("Game finalization\n");

    // if(cursor) cursor->free();
    // if(screen) screen->free();
    graph->finalize();

    return 0;
}
