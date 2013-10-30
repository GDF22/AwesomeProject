/* 
 * File:   Object.h
 * Author: Administrator
 *
 * Created on 29 octobre 2013, 11:12
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <vector>
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

using namespace std;

class Object {
public:
    Object();
    virtual ~Object();
private:
    vector<glVertex3f> listeSommets;
    glVertex3f vertex;
};

#endif	/* OBJECT_H */

