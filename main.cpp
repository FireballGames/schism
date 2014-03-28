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

    gui = new gameGUI;

    res = gui->initialize();
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

    /*
    res = gui->game();
    if(res != 0){
        return finalize(4, res);
    }
    */

    return finalize();
}
