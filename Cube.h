/* 
 * File:   Cube.h
 * Author: Administrator
 *
 * Created on 31 octobre 2013, 19:25
 */

#ifndef CUBE_H
#define	CUBE_H

#include "Object.h"

class Cube : public Object{
public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();
private:

};

#endif	/* CUBE_H */

