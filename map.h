/*
 * File:   map.h
 * Author: d2emon
 *
 * Created on 23 Январь 2014 г., 0:13
 */

#ifndef MAP_H
#define	MAP_H

#include "location.h"

const unsigned int max_x = 255;
const unsigned int max_y = 255;

class map {
public:
    location *locations[max_x][max_y];

    map();
    map(const map& orig);
    virtual ~map();
    int generate();
    int save(const char* filename);
    int load(const char* filename);
private:
    int flow(int x, int y, int terr_type, int iterations);
    int can_flow(int x, int y, int terr_type);
};

#endif	/* MAP_H */

