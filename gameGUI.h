/*
 * File:   gameGUI.h
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 23:02
 */

#ifndef GAMEGUI_H
#define	GAMEGUI_H

#include "map.h"
#include "D2SDL/D2SDLgraph.h"
#include "interface/mapBig.h"
#include "interface/mapMini.h"

class gameGUI {
public:
    gameGUI();
    gameGUI(const gameGUI& orig);
    virtual ~gameGUI();

    int initialize(int windowed, int highres);
    int title();
    int mainmenu();
    int game();
    int finalize();
private:
    D2SDLgraph* graph;
    D2SDLimage* screen;
    D2SDLcursor* cursor;

    int mainLoop();
};

#endif	/* GAMEGUI_H */

