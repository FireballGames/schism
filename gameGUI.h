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
    /*
     * Graphics flags
     */
    int windowed;
    int highres;

    /*
     * Constructor & Destructor
     */
    gameGUI();
    virtual ~gameGUI();

    /*
     * Game stages
     */
    int initialize();
    int title();
    int mainmenu();
    int game();
    int finalize();
private:
    D2SDLgraph*  graph;  // Game graphics
    D2SDLcursor* cursor; // Game cursor
    map* m; // Game map
};

#endif	/* GAMEGUI_H */

