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
    map* m;
    int x;
    int y;

    gameGUI();
    gameGUI(const gameGUI& orig);
    virtual ~gameGUI();

    int initialize();
    int title();
    int mainmenu();
    int game();
    int finalize();
private:
    D2SDLgraph* graph;
    D2SDLimage* screen;
    D2SDLimage* cursor;
    mapBig* bigmap;
    mapMini* minimap;

    int mainLoop();
    int showmap();

    int moveView(int dx, int dy);
    void moveMouse(int x, int y);
};

#endif	/* GAMEGUI_H */

