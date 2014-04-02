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

const int DEFAULT_WINDOWED = 1;
const int DEFAULT_HIGHRES  = 0;

const char* IMG_CURSOR = "images/cursor.png";

/*
const int   UNIT_X   = 180;
const int   UNIT_Y   = 180;
const char* IMG_UNIT       = "images/unit.gif";
*/

//const char* IMG_BACKGROUND = "images/background.bmp";

/*
const int tile_x = 400; //350
const int tile_y = 256; //200
*/

gameGUI::gameGUI()
{
    windowed = DEFAULT_WINDOWED;
    highres  = DEFAULT_HIGHRES;

    graph  = NULL;
    cursor = NULL;
}

gameGUI::~gameGUI()
{
}

/**
 * Intializing game
 * @return int errorcode 0 if success
 */
int gameGUI::initialize()
{
    int errorcode = 0;

    printf("Game initialization\n");

    graph     = new D2SDLgraph;
    errorcode = graph->initialize(!windowed, highres);
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
int gameGUI::title()
{
    int errorcode = 0;

    printf("Showing title screen\n");

    /*
     * Fireball logo screen
     */
    screenLogoFireball* logo1 = NULL;
    logo1 = new screenLogoFireball(graph);
    errorcode = logo1->show();
    //delete logo1;

    if(graph->stopped) return 1;

    /*
     * Some game preparations
     */
    cursor = new D2SDLcursor;
    cursor->load(IMG_CURSOR);

    /*
     * SDL logo screen
     */
    screenLogoSDL* logo2 = NULL;
    logo2 = new screenLogoSDL(graph);
    errorcode = logo2->show();
    //delete logo2;
    if(graph->stopped) return 1;

    return errorcode;
}

/**
 * Using main menu screen
 * @return int errorcode 0 if success
 */
int gameGUI::mainmenu()
{
    int errorcode = 0;

    printf("Showing mainmenu\n");

    /*
     * Main menu screen
     */
    screenLogoSchism* menuScreen = NULL;
    menuScreen = new screenLogoSchism(graph);
    menuScreen->cursor = cursor;
    errorcode = menuScreen->show();
    delete menuScreen;
    if(graph->stopped) return 1;

    return errorcode;
}

/**
 * Main game screen
 * @return int errorcode 0 if success
 */
int gameGUI::game()
{
    int errorcode = 0;

    printf("Main game screen\n");

    // Main screen
    screenMain* main_screen = NULL;
    main_screen = new screenMain(graph);
    main_screen->cursor = cursor;
    main_screen->show();
    if(graph->stopped) return 1;

    return errorcode;
}

int gameGUI::finalize()
{
    printf("Game finalization\n");

    //if(cursor) cursor->free();
    graph->finalize();

    return 0;
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
