/*
 * File:   map.h
 * Author: d2emon
 *
 * Created on 23 Январь 2014 г., 0:13
 */

#ifndef MAP_H
#define	MAP_H

#include "location.h"

class map {
public:
    location *locations[256][256];

    map();
    map(const map& orig);
    virtual ~map();
    int generate();
private:
    int flow(int x, int y, int terr_type, int iterations);
    int can_flow(int x, int y, int terr_type);
};

#endif	/* MAP_H */

