/* 
 * File:   Controler.h
 * Author: Administrator
 *
 * Created on 28 octobre 2013, 18:13
 */

#ifndef CONTROLER_H
#define	CONTROLER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Coord3D.h"
#include "Fenetre.h"
#include "Camera.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

class Controler {
public:
    Controler();
    virtual ~Controler();
    void run();
private:
    KeyboardEvent keyboard;
    MouseEvent mouse;
    Camera camera;
            
};

#endif	/* CONTROLER_H */

