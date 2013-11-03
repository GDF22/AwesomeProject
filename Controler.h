/* 
 * File:   Controler.h
 * Author: Administrator
 *
 * Created on 28 octobre 2013, 18:13
 */

#ifndef CONTROLER_H
#define	CONTROLER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <SDL/SDL.h>
#include <gl/glu.h>
#include "Coord3D.h"
#include "Fenetre.h"
#include "Camera.h"
#include "KeyAssignment.h"
#include "Event.h"
#include "FrameManager.h"
#include "Face.h"
#include "Object.h"
#include "Panel.h"



using namespace std;

class Controler {
public:
    Controler();
    virtual ~Controler();
    void run();
private:
    KeyAssignment ka;
    Event event;
    Camera camera;
};

#endif	/* CONTROLER_H */

