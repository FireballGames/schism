/*
 * File:   gameGUI.h
 * Author: d2emon
 *
 * Created on 22 Январь 2014 г., 23:02
 */

#ifndef GAMEGUI_H
#define	GAMEGUI_H

#include "SDLgraph.h"
#include "map.h"
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
    int mainLoop();
    int finalize();
    int showmap();
private:
    SDLgraph*  graph;
    mapBig* bigmap;
    mapMini* minimap;
};

#endif	/* GAMEGUI_H */

