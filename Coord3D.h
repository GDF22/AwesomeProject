/* 
 * File:   Coord3D.h
 * Author: Administrator
 *
 * Created on 18 octobre 2013, 23:16
 */

#ifndef COORD3D_H
#define	COORD3D_H

#include <iostream>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <SDL/SDL.h>

using namespace std;

using namespace std;

class Coord3D {
public:
    Coord3D();
    Coord3D(double x, double y, double z);
    
    double getX();
    double getY();
    double getZ();
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    
    double distance(Coord3D p);
    Coord3D vectUnitaire(Coord3D direction);
    
    bool equal(Coord3D a);
    string toString();
    
    SDL_Rect toSDL_Rect();
private:
    double x, y, z;
};

#endif	/* COORD3D_H */

