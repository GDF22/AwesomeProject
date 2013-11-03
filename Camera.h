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

#include "Event.h"
#include "Coord3D.h"


using namespace std;

class Camera {
public:
    Camera();
    Camera(Coord3D pos, Coord3D at, Coord3D up);
    
    void placeCamera();
    
    void updateView(int* mouse);
    
    void forward();
    void backward();
    void lateralLeft();
    void lateralRight();
    void up();
    void down();
    void lookUp();
    void lookDown();
    void lookLeft();
    void lookRight();
    
    Coord3D getPos();
    Coord3D getAt();
    void setPos(Coord3D pos);
    void setAt(Coord3D at);
    
private:
    Coord3D pos;
    Coord3D at;
    double latitude;
    double longitude;
    float vitesseDep;
    float vitesseVue;
};

#endif	/* CAMERA_H */

