/* 
 * File:   Camera.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 23:14
 */

#include "Camera.h"

using namespace std;

Camera::Camera() {
    pos = Coord3D(0, 0, 0);
    at = Coord3D(0, 0, 0);
    vitesseDep = 0;
    vitesseVue = 0;
    latitude = 0;
    longitude = 0;
}

Camera::Camera(Coord3D pos, Coord3D at, Coord3D up) {
    this->pos = pos;
    this->at = at;
    vitesseDep = 0.1;
    vitesseVue = 0.005;
    latitude = 0;
    longitude = 0;
}

void Camera::placeCamera() {
    at.setX(pos.getX() + cos(latitude)*cos(longitude));
    at.setY(pos.getY() + cos(latitude)*sin(longitude));
    at.setZ(pos.getZ() + sin(latitude));
    gluLookAt((GLdouble)pos.getX(), (GLdouble)pos.getY(), (GLdouble)pos.getZ(), (GLdouble)at.getX(), (GLdouble)at.getY(), (GLdouble)at.getZ(), 0, 0, 1);
}



void Camera::updateView(int* mouse) {    
    int i;
    for(i = 0; i < mouse[0]; i++) {
        this->lookLeft();
    }
    for(i = 0; i > mouse[0]; i--) {
        this->lookRight();
    }
    for(i = 0; i < mouse[1]; i++) {
        this->lookUp();
    }
    for(i = 0; i > mouse[1]; i--) {
        this->lookDown();
    }
    
    /*for(i = 0; i < mouse.wheel; i++) {
        this->monte();
    }
    for(i = 0; i > mouse.wheel; i--) {
        this->descend();
    }*/
}



void Camera::forward() {
    Coord3D vect = pos.vectUnitaire(at);
    pos.setX(pos.getX() + vect.getX()*vitesseDep);
    pos.setY(pos.getY() + vect.getY()*vitesseDep);
    pos.setZ(pos.getZ() + vect.getZ()*vitesseDep);
    at.setX(at.getX() + vect.getX()*vitesseDep);
    at.setY(at.getY() + vect.getY()*vitesseDep);
    at.setZ(at.getZ() + vect.getZ()*vitesseDep);
}


void Camera::backward() {
    Coord3D vect = pos.vectUnitaire(at);
    pos.setX(pos.getX() - vect.getX()*vitesseDep);
    pos.setY(pos.getY() - vect.getY()*vitesseDep);
    pos.setZ(pos.getZ() - vect.getZ()*vitesseDep);
    at.setX(at.getX() - vect.getX()*vitesseDep);
    at.setY(at.getY() - vect.getY()*vitesseDep);
    at.setZ(at.getZ() - vect.getZ()*vitesseDep);
}


void Camera::lateralLeft() {
    pos.setX(pos.getX() - sin(longitude)*vitesseDep);
    pos.setY(pos.getY() + cos(longitude)*vitesseDep);
    at.setX(at.getX() - sin(longitude)*vitesseDep);
    at.setY(at.getY() + cos(longitude)*vitesseDep);
}


void Camera::lateralRight() {
    pos.setX(pos.getX() + sin(longitude)*vitesseDep);
    pos.setY(pos.getY() - cos(longitude)*vitesseDep);
    at.setX(at.getX() + sin(longitude)*vitesseDep);
    at.setY(at.getY() - cos(longitude)*vitesseDep);
}


void Camera::up() {
    pos.setZ(pos.getZ() + vitesseDep*2);
    at.setZ(at.getZ() + vitesseDep*2);
}


void Camera::down() {
    pos.setZ(pos.getZ() - vitesseDep*2);
    at.setZ(at.getZ() - vitesseDep*2);
}


void Camera::lookUp() {
    if(latitude + vitesseVue < M_PI/2) {
        latitude += vitesseVue;
    }
}


void Camera::lookDown() {
    if(latitude - vitesseVue > -M_PI/2) {
        latitude -= vitesseVue;
    }
}


void Camera::lookLeft() {
    longitude += vitesseVue;
}


void Camera::lookRight() {
    longitude -=  vitesseVue;
}



Coord3D Camera::getPos() {
    return(pos);
}

Coord3D Camera::getAt() {
    return(at);
}

void Camera::setPos(Coord3D pos) {
    this->pos = pos;
}

void Camera::setAt(Coord3D at) {
    this->at = at;
}