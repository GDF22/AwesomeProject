/* 
 * File:   World.h
 * Author: Administrator
 *
 * Created on 3 novembre 2013, 14:34
 */

#ifndef WORLD_H
#define	WORLD_H

#include <iostream>
#include <fstream>
#include <gl/gl.h>
#include <vector>
#include "Object.h"

using namespace std;

class World {
public:
    World();
    World(const World& orig);
    virtual ~World();
    
    void addObject(Object obj);
    bool addObject(char* filename);
    
    void removeObject(Object obj);
    void removeObject(int obj);
    
    void draw();
private:
    vector<Object> listObject;

};

#endif	/* WORLD_H */

