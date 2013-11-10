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
#include <typeinfo>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <gl/glu.h>

#include "Action.h"
#include "Coord3D.h"
#include "Camera.h"
#include "KeyAssignment.h"
#include "Event.h"
#include "FrameManager.h"
#include "Face.h"
#include "Object.h"
#include "Panel.h"
#include "World.h"
#include "Button.h"

using namespace std;

class Controler {
public:
    Controler();
    virtual ~Controler();
    
    void init();
    void quit();
    void run();
    
    void glEnable3D();
    void glDisable3D();
    void glEnable2D();
    void glDisable2D();
    
    void action(Action act);
    void actionOnClick(pair<int,int> coord);
    
private:
    SDL_Window* pWindow;
    KeyAssignment ka;
    Event event;
    Camera* camera;
    Panel* twoDim;
    
};

#endif	/* CONTROLER_H */

