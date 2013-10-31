/* 
 * File:   Face.h
 * Author: Administrator
 *
 * Created on 30 octobre 2013, 10:23
 */

#ifndef FACE_H
#define	FACE_H

#include <cstdio>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Coord3D.h"

using namespace std;

class Face {
public:
    Face(vector<Coord3D> vect, Coord3D colorFace, Coord3D colorEdge);
    virtual ~Face();
    
    Coord3D getColorFace();
    Coord3D getColorEdge();
    void setColor(Coord3D face, Coord3D edge);
    
    void drawFace();
    void drawEdge();
    void toString();
private:
    vector<Coord3D*> tabVertex;   // liste des pointeurs de sommet
    Coord3D colorFace;
    Coord3D colorEdge;
};

#endif	/* FACE_H */

