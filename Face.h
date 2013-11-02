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
    Face(vector<int> vect);
    Face(vector<int> vect, Coord3D colorFace, Coord3D colorEdge);
    virtual ~Face();
    
    int getVertex(int i);
    Coord3D getColorFace();
    Coord3D getColorEdge();
    int getSize();
    
    void setColor(Coord3D face, Coord3D edge);
    
    void applyColorFace();
    void applyColorEdge();
    
    void removeVertex(int vertex);
    
    void drawFace();
    void drawEdge();
    string toString();
private:
    vector<int> listVertex;   // Liste des sommets
    Coord3D colorFace;      // Couleur de la face
    Coord3D colorEdge;      // Couleur des arêtes
};

#endif	/* FACE_H */

