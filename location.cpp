/*
 * File:   location.cpp
 * Author: d2emon
 *
 * Created on 23 Январь 2014 г., 0:07
 */

#include "location.h"
#include <cstdlib>

location::location() {
    randomloc();
}

location::location(const location& orig) {
}

location::~location() {
}

void location::randomloc() {
    loctype = 0; //rand() % 4;
    style   = rand() % 4;
}
