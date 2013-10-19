/* 
 * File:   Coord3D.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 23:16
 */

#include <math.h>
#include "Coord3D.h"

Coord3D::Coord3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Coord3D::Coord3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


double Coord3D::getX() {
    return(x);
}

double Coord3D::getY() {
    return(y);
}

double Coord3D::getZ() {
    return(z);
}

void Coord3D::setX(double x) {
    this->x = x;
}

void Coord3D::setY(double y) {
    this->y = y;
}

void Coord3D::setZ(double z) {
    this->z = z;
}



double Coord3D::distance(Coord3D p) {
    return(sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2) + pow(p.z - this->z, 2)));
}


Coord3D Coord3D::vectUnitaire(Coord3D direction) {
    float vectx, vecty, vectz, norme;
    norme = this->distance(direction);
    vectx = (direction.x - this->x);
    vecty = (direction.y - this->y);
    vectz = (direction.z - this->z);
    return(Coord3D(vectx, vecty, vectz));
}


string Coord3D::toString() {
    string out = "";
    //out = "("+x+", "+y+", "+z+")";
    return(out);
}