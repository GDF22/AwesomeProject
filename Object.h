/* 
 * File:   Object.h
 * Author: Administrator
 *
 * Created on 29 octobre 2013, 11:12
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <vector>
#include "Coord3D.h"
#include "Face.h"

class Object {
public:
    Object();
    virtual ~Object();
    
    
    void drawFace();
    void drawEdge();
private:
    vector<Coord3D> listVertex;
    vector<Face> listFace;
};

#endif	/* OBJECT_H */

