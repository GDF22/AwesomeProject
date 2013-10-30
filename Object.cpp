/* 
 * File:   Object.cpp
 * Author: Administrator
 * 
 * Created on 29 octobre 2013, 11:12
 */

#include "Object.h"

Object::Object() {
    listeSommets = new vector<glVertex3f>;
    glVertex3f g;
}


Object::~Object() {
}

