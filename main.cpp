/*
 * File:   main.cpp
 * Author: d2emon
 *
 * Created on 20 Январь 2014 г., 22:39
 */

//#define	FULLSCREEN
//#define HIGHRES

#include <cstdlib>
#include <iostream>
#include "gameGUI.h"

using namespace std;

gameGUI* gui = NULL;

int finalize(int errorcode = 0, int res = 0) {
    if(res<0) {
        if(errorcode == 1) {
            printf("Initialization error\n");
        } else if (errorcode == 2) {
            printf("Title error");
        } else if (errorcode == 3) {
            printf("Main menu error");
        } else if (errorcode == 4) {
            printf("Main loop error");
        }
    }

    if(gui->finalize() < 0){
        printf("Finalization error");
        return 5;
    }

    return errorcode;
}

/*
 *
 */
int main(int argc, char** argv) {
    int res = 0;

#ifdef FULLSCREEN
    int windowed = false;
#else
    int windowed = true;
#endif

#ifdef HIGHRES
    int highres = true;
#else
    int highres = false;
#endif

    for(int i=0; i<argc; i++)
    {
        if(argv[i] == "-w")
        {
            windowed = true;
        }
        else if(argv[i] == "-f")
        {
            windowed = false;
        }
        else if(argv[i] == "-h")
        {
            highres = true;
        }
        else if(argv[i] == "-l")
        {
            highres = false;
        }
    }

    gui = new gameGUI;

    res = gui->initialize(windowed, highres);
    if(res != 0){
        return finalize(1, res);
    }

    res = gui->title();
    if(res != 0){
        return finalize(2, res);
    }

    res = gui->mainmenu();
    if(res != 0){
        return finalize(3, res);
    }

    res = gui->game();
    if(res != 0){
        return finalize(4, res);
    }

    return finalize();
}
