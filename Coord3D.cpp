/* 
 * File:   Coord3D.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 23:16
 */

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

SDL_Rect Coord3D::toSDL_Rect(){
    SDL_Rect result;
    result.x = this->x;
    result.y = this->y;
    return result;
}


double Coord3D::distance(Coord3D* p) {
    return(sqrt(pow(p->x - this->x, 2) + pow(p->y - this->y, 2) + pow(p->z - this->z, 2)));
}


Coord3D Coord3D::vectUnitaire(Coord3D direction) {
    float vectx, vecty, vectz, norme;
    norme = this->distance(&direction);
    vectx = (direction.x - this->x);
    vecty = (direction.y - this->y);
    vectz = (direction.z - this->z);
    return(Coord3D(vectx, vecty, vectz));
}


bool Coord3D::equal(Coord3D a) {
    return(a.getX() == this->x && a.getY() == this->y && a.getZ() == this->z);
}


Coord3D Coord3D::operator+(Coord3D coord) {
    return(Coord3D(this->x + coord.getX(), this->y + coord.getY(), this->z + coord.getZ()));
}



string Coord3D::toString() {
    string out = "";
    std::ostringstream sx, sy, sz;
    sx << x;
    sy << y;
    sz << z;
    out = "(" + sx.str() + ", " + sy.str() + ", " + sz.str() + ")";
    return(out);
}