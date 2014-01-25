/* 
 * File:   map.cpp
 * Author: d2emon
 * 
 * Created on 23 Январь 2014 г., 0:13
 */

#include "map.h"
#include "location.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>

map::map() {
    srand(time( NULL ));
    
    //locations = new location*[256];
    for(int i=0; i<256; i++) {
        //locations[i] = new location[256];
        for(int j=0; j<256; j++) {
            location* loc = new location;
            locations[i][j] = loc;
            //printf("%d:%d,", loc->loctype, loc->style);
        }
        //printf("\n");
    }
}

map::map(const map& orig) {
}

map::~map() {
    for(int i=0; i<256; i++) {
        //delete[] locations[i];
    }
    //delete[] locations;
}

