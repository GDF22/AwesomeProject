/* 
 * File:   Object.h
 * Author: Administrator
 *
 * Created on 29 octobre 2013, 11:12
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <iterator>
#include "Coord3D.h"
#include "Face.h"

class Object {
public:
    Object();
    virtual ~Object();
    
    void addVertex(Coord3D vertex);
    
    void removeVertex(int vertex);
    void removeVertex(Coord3D vertex);
    void actualisationFace(int vertex);

    void addFace(vector<int> listVertex, Color colorFace, Color colorEdge);
    void addFace(Face face);
    
    void drawFace();
    void drawEdge();
    
    int nbVertex();
    int nbFace();
    
    string toString();
private:
    Coord3D position;
    vector<Coord3D> listVertex;
    vector<Face> listFace;
    bool move;
};

#endif	/* OBJECT_H */

