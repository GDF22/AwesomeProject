/* 
 * File:   Face.h
 * Author: Administrator
 *
 * Created on 30 octobre 2013, 10:23
 */

#ifndef FACE_H
#define	FACE_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Coord3D.h"

using namespace std;

class Face {
public:
    Face(vector<Coord3D> vect);
    virtual ~Face();
    
    void draw();
    void toString();
private:
    vector<Coord3D*> tabVertex;   // liste des pointeurs de sommet
};

#endif	/* FACE_H */

