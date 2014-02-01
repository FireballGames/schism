/*
 * File:   main.cpp
 * Author: d2emon
 *
 * Created on 20 Январь 2014 г., 22:39
 */

#include <cstdlib>
#include <iostream>
#include "gameGUI.h"

using namespace std;

gameGUI* gui = NULL;

/*
 *
 */
int main(int argc, char** argv) {
    gui = new gameGUI;

    if(gui->initialize() < 0){
        printf("Initialization error\n");
        return 1;
    }

    if(gui->title() < 0){
        printf("Title error");
        return 2;
    }

    if(gui->mainLoop() < 0){
        printf("Main loop error");
        return 3;
    }

    if(gui->finalize() < 0){
        printf("Finalization error");
        return 4;
    }

    return 0;
}
