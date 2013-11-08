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
#include <cmath>
#include <vector>
#include <iterator>
#include "Coord3D.h"
#include "Face.h"

using namespace std;

class Object {
public:
    Object();
    Object(string name, Coord3D* position);
    virtual ~Object();
    
    Coord3D* getPosition();
    void setPosition(Coord3D* position);
    
    void addVertex(Coord3D vertex);
    
    void removeVertex(int vertex);
    void removeVertex(Coord3D vertex);
    void actualisationFace(int vertex);

    void addFace(vector<int> listVertex, Color* colorFace, Color* colorEdge);
    void addFace(Face* face);

    void rotate(double rotH, double rotV, double rotJSPQ);
    void rotateHorizontal(Coord3D* vertex, double angle);
    void rotateVertical(Coord3D* vertex, double angle);
    void rotatejesaispasquoi(Coord3D* vertex, double angle);
    void drawFace();
    void drawEdge();
    
    int nbVertex();
    int nbFace();
    
    string toString();
private:
    string name;
    Coord3D* position;
    
    vector<Coord3D> listVertex;
    vector<Face> listFace;
    bool move;
};

#endif	/* OBJECT_H */

