/*
 * File:   main.cpp
 * Author: d2emon
 *
 * Created on 20 Январь 2014 г., 22:39
 */

#define FULLSCREEN
#define HIGHRES

#include <cstdlib>
#include <iostream>
#include "gameGUI.h"

using namespace std;

const char* FLAG_WINDOWED   = "w";
const char* FLAG_FULLSCREEN = "f";
const char* FLAG_HIGHRES    = "h";
const char* FLAG_LOWRES     = "l";

const int ERROR_RESULT = -1;

const int ERROR_INIT     = 1;
const int ERROR_TITLE    = 2;
const int ERROR_MAINMENU = 3;
const int ERROR_MAINLOOP = 4;
const int ERROR_FINALIZE = 5;

const int ERROR_NOT_FINALIZED = 255;

gameGUI* gui = NULL;

/**
 * Properly closing the game
 * @param int errorcode Error displayed by the game
 * @param int res       Resulted number of function
 */
void finalize(int errorcode = 0, int res = 0)
{
    if(gui->finalize() < 0)
    {
        errorcode = ERROR_FINALIZE;
        res       = ERROR_RESULT;
    }

    if(res<0)
    {
        switch(errorcode)
        {
            case ERROR_INIT:
                printf("Initialization error\n");
                break;
            case ERROR_TITLE:
                printf("Title error\n");
                break;
            case ERROR_MAINMENU:
                printf("Main menu error\n");
                break;
            case ERROR_MAINLOOP:
                printf("Main loop error\n");
                break;
            case ERROR_FINALIZE:
                printf("Finalization error\n");
                break;
        }
    }
    else
    {
        errorcode = 0;
    }

    exit(errorcode);
}

/**
 * Running stage with exit on error
 * @param int res Stage result
 * @param int errorcode Stage errorcode
 */
void run_stage(int res = 0, int errorcode = 0)
{
    if(res){
        finalize(errorcode, res);
    }
}

/**
 * Game main function
 */
int main(int argc, char** argv) {

    gui = new gameGUI;

#ifdef FULLSCREEN
    gui->windowed = 0;
#else
    gui->windowed = 1;
#endif

#ifdef HIGHRES
    gui->highres = 1;
#else
    gui->highres = 0;
#endif

    /*
     * Applying flags
     */
    for(int i=0; i<argc; i++)
    {
        if(argv[i] == FLAG_WINDOWED)
        {
            gui->windowed = 1;
        }
        else if(argv[i] == FLAG_FULLSCREEN)
        {
            gui->windowed = 0;
        }
        else if(argv[i] == FLAG_HIGHRES)
        {
            gui->highres = 1;
        }
        else if(argv[i] == FLAG_LOWRES)
        {
            gui->highres = 0;
        }
    }

    run_stage(gui->initialize(), ERROR_INIT    );
    run_stage(gui->title(),      ERROR_TITLE   );
    run_stage(gui->mainmenu(),   ERROR_MAINMENU);
    run_stage(gui->game(),       ERROR_MAINLOOP);

    finalize();

    return ERROR_NOT_FINALIZED;
}
