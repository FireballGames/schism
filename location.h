/*
 * File:   location.h
 * Author: d2emon
 *
 * Created on 23 Январь 2014 г., 0:07
 */

#ifndef LOCATION_H
#define	LOCATION_H

class location {
public:
    int loctype;
    int style;
    int object;

    location();
    location(const location& orig);
    virtual ~location();
    void randomloc();
private:

};

#endif	/* LOCATION_H */

