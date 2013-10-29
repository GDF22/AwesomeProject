/* 
 * File:   Camera.h
 * Author: Administrator
 *
 * Created on 18 octobre 2013, 23:14
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <GL/glu.h>
#include <SDL/SDL.h>
#include <cstdio>
#include <math.h>

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Coord3D.h"


using namespace std;

class Camera {
public:
    Camera();
    Camera(Coord3D pos, Coord3D at, Coord3D up);
    
    void placeCamera();
    
    void deplacement(KeyboardEvent keyboard, MouseEvent mouse);
    void avance();
    void recule();
    void depGauche();
    void depDroite();
    void rotGauche();
    void rotDroite();
    void rotHaut();
    void rotBas();
    void monte();
    void descend();
    
    Coord3D getPos();
    Coord3D getAt();
private:
    Coord3D pos;
    Coord3D at;
    Coord3D up;
    double latitude;
    double longitude;
    float vitesseDep;
    float vitesseVue;
};

#endif	/* CAMERA_H */

