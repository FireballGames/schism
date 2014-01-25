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

class gameGUI {
public:
    map* m;
    
    gameGUI();
    gameGUI(const gameGUI& orig);
    virtual ~gameGUI();
    
    int initialize();
    int title();
    int mainLoop();
    int finalize();
private:
    SDLgraph*  graph;
};

#endif	/* GAMEGUI_H */

