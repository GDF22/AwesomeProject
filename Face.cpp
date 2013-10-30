/* 
 * File:   Face.cpp
 * Author: Administrator
 * 
 * Created on 30 octobre 2013, 10:23
 */

#include "Face.h"
#include "Coord3D.h"

using namespace std;

Face::Face(vector<Coord3D> vect) {
    int i;
    for(i = 0; i < vect.size(); i++) {
        tabVertex.push_back(&vect[i]);
    }
}

Face::~Face() {
}


void Face::toString() {
    int i;
    for(i = 0; i < tabVertex.size(); i++) {
        (tabVertex[i])->toString();
    }
}

void Face::draw() {    
    glBegin(GL_POLYGON);
        glColor3ub(255,0,0);
        for(int i = 0; i < tabVertex.size(); i++) {
            glVertex3f((*tabVertex[i]).getX(),(*tabVertex[i]).getY(),(*tabVertex[i]).getZ());
        }
    glEnd();
}