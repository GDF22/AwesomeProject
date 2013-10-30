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
private:
    //vector<Coord3D> listeSommet;
    //vector<Face> listeFace;
};

#endif	/* OBJECT_H */

