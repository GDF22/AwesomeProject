/* 
 * File:   Camera.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 23:14
 */

#include "Camera.h"
#include "Coord3D.h"
#include <GL/glu.h>
#include <cstdio>
#include <math.h>

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
    vitesseDep = 0.005;
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



void Camera::deplacement(EvenementClavier clavier) {
    if(clavier.left) {
        this->depGauche();
    }
    if(clavier.right) {
        this->depDroite();
    }
    if(clavier.up) {
        this->avance();
    }
    if(clavier.down) {
        this->recule();
    }
    if(clavier.k4) {
        this->rotGauche();
    }
    if(clavier.k6) {
        this->rotDroite();
    }
    if(clavier.k8) {
        this->haut();
    }
    if(clavier.k2) {
        this->bas();
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
    pos.setX(pos.getX() - (at.getY() - pos.getY())*vitesseDep);
    pos.setY(pos.getY() + (at.getX() - pos.getX())*vitesseDep);
    at.setX(at.getX() -(at.getY() - pos.getY())*vitesseDep);
    at.setY(at.getY() + (at.getX() - pos.getX())*vitesseDep);
}

void Camera::depDroite() {
    pos.setX(pos.getX() + (at.getY() - pos.getY())*vitesseDep);
    pos.setY(pos.getY() - (at.getX() - pos.getX())*vitesseDep);
    at.setX(at.getX() + (at.getY() - pos.getY())*vitesseDep);
    at.setY(at.getY() - (at.getX() - pos.getX())*vitesseDep);
}


void Camera::rotGauche() {
    longitude += vitesseVue;
}

void Camera::rotDroite() {
    longitude -=  vitesseVue;
}

void Camera::haut() {
    if(latitude + vitesseVue < M_PI/2) {
        latitude += vitesseVue;
    }
}

void Camera::bas() {
    if(latitude - vitesseVue > -M_PI/2) {
        latitude -= vitesseVue;
    }
}