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
#include "Color.h"


using namespace std;

class Face {
public:
    Face();
    Face(vector<int> vect);
    Face(vector<int> vect, Color colorFace, Color colorEdge);
    virtual ~Face();
    
    int getVertex(int i);
    Color getColorFace();
    Color getColorEdge();
    int getSize();
        
    void applyColorFace();
    void applyColorEdge();
    
    void removeVertex(int vertex);
    
    void drawFace();
    void drawEdge();
    string toString();
private:
    vector<int> listVertex;   // Liste des sommets
    Color colorFace;      // Couleur de la face
    Color colorEdge;      // Couleur des arêtes
};

#endif	/* FACE_H */

