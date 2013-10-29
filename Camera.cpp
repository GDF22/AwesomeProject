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
    up = Coord3D(0, 0, 1);
    vitesseDep = 0;
    vitesseVue = 0;
    latitude = 0;
    longitude = 0;
}

Camera::Camera(Coord3D pos, Coord3D at, Coord3D up) {
    this->pos = pos;
    this->at = at;
    this->up = up;
    vitesseDep = 0.1;
    vitesseVue = 0.005;
    latitude = 0;
    longitude = 0;
}

void Camera::placeCamera() {
    at.setX(pos.getX() + cos(latitude)*cos(longitude));
    at.setY(pos.getY() + cos(latitude)*sin(longitude));
    at.setZ(pos.getZ() + sin(latitude));
    gluLookAt((GLdouble)pos.getX(), (GLdouble)pos.getY(), (GLdouble)pos.getZ(), (GLdouble)at.getX(), (GLdouble)at.getY(), (GLdouble)at.getZ(), (GLdouble)up.getX(), (GLdouble)up.getY(), (GLdouble)up.getZ());
}



void Camera::deplacement(KeyboardEvent keyboard, MouseEvent mouse) {
    if(keyboard.left) {
        this->depGauche();
    }
    if(keyboard.right) {
        this->depDroite();
    }
    if(keyboard.up) {
        this->avance();
    }
    if(keyboard.down) {
        this->recule();
    }
    if(keyboard.k4) {
        this->rotGauche();
    }
    if(keyboard.k6) {
        this->rotDroite();
    }
    if(keyboard.k8) {
        this->rotHaut();
    }
    if(keyboard.k2) {
        this->rotBas();
    }
    
    int i;
    for(i = 0; i < mouse.sourisdx; i++) {
        this->rotGauche();
    }
    for(i = 0; i > mouse.sourisdx; i--) {
        this->rotDroite();
    }
    for(i = 0; i < mouse.sourisdy; i++) {
        this->rotHaut();
    }
    for(i = 0; i > mouse.sourisdy; i--) {
        this->rotBas();
    }
    
    for(i = 0; i < mouse.wheel; i++) {
        this->monte();
    }
    for(i = 0; i > mouse.wheel; i--) {
        this->descend();
    }
}



void Camera::avance() {
    Coord3D vect = pos.vectUnitaire(at);
    pos.setX(pos.getX() + vect.getX()*vitesseDep);
    pos.setY(pos.getY() + vect.getY()*vitesseDep);
    pos.setZ(pos.getZ() + vect.getZ()*vitesseDep);
    at.setX(at.getX() + vect.getX()*vitesseDep);
    at.setY(at.getY() + vect.getY()*vitesseDep);
    at.setZ(at.getZ() + vect.getZ()*vitesseDep);
}


void Camera::recule() {
    Coord3D vect = pos.vectUnitaire(at);
    pos.setX(pos.getX() - vect.getX()*vitesseDep);
    pos.setY(pos.getY() - vect.getY()*vitesseDep);
    pos.setZ(pos.getZ() - vect.getZ()*vitesseDep);
    at.setX(at.getX() - vect.getX()*vitesseDep);
    at.setY(at.getY() - vect.getY()*vitesseDep);
    at.setZ(at.getZ() - vect.getZ()*vitesseDep);
}

void Camera::depGauche() {
    pos.setX(pos.getX() - sin(longitude)*vitesseDep);
    pos.setY(pos.getY() + cos(longitude)*vitesseDep);
    at.setX(at.getX() - sin(longitude)*vitesseDep);
    at.setY(at.getY() + cos(longitude)*vitesseDep);
}

void Camera::depDroite() {
    pos.setX(pos.getX() + sin(longitude)*vitesseDep);
    pos.setY(pos.getY() - cos(longitude)*vitesseDep);
    at.setX(at.getX() + sin(longitude)*vitesseDep);
    at.setY(at.getY() - cos(longitude)*vitesseDep);
}


void Camera::rotGauche() {
    longitude += vitesseVue;
}

void Camera::rotDroite() {
    longitude -=  vitesseVue;
}

void Camera::rotHaut() {
    if(latitude + vitesseVue < M_PI/2) {
        latitude += vitesseVue;
    }
}

void Camera::rotBas() {
    if(latitude - vitesseVue > -M_PI/2) {
        latitude -= vitesseVue;
    }
}

void Camera::monte() {
    pos.setZ(pos.getZ() + vitesseDep*2);
    at.setZ(at.getZ() + vitesseDep*2);
}

void Camera::descend() {
    pos.setZ(pos.getZ() - vitesseDep*2);
    at.setZ(at.getZ() - vitesseDep*2);
}