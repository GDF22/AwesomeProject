/* 
 * File:   Camera.h
 * Author: Administrator
 *
 * Created on 18 octobre 2013, 23:14
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <map>
#include "EvenementClavier.h"
#include "Coord3D.h"

using namespace std;

class Camera {
public:
    Camera();
    Camera(Coord3D pos, Coord3D at, Coord3D up);
    
    void placeCamera();
    
    void deplacement(EvenementClavier clavier);
    void avance();
    void recule();
    void depGauche();
    void depDroite();
    void rotGauche();
    void rotDroite();
    void haut();
    void bas();
    
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

