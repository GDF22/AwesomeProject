/* 
 * File:   Face.cpp
 * Author: Administrator
 * 
 * Created on 30 octobre 2013, 10:23
 */

#include "Face.h"
#include "Coord3D.h"

using namespace std;

Face::Face(vector<int> vect) {
    for(int i = 0; i < vect.size(); i++) {
        listVertex.push_back(vect[i]);
    }
}

Face::Face(vector<int> vect, Coord3D colorFace, Coord3D colorEdge) {
    for(int i = 0; i < vect.size(); i++) {
        listVertex.push_back(vect[i]);
    }
    this->setColor(colorFace, colorEdge);
}

Face::~Face() {
}


int Face::getVertex(int i) {
    return(listVertex[i]);
}

Coord3D Face::getColorFace() {
    return(this->colorFace);
}

Coord3D Face::getColorEdge() {
    return(this->colorEdge);
}


int Face::getSize() {
    return(this->listVertex.size());
}


void Face::setColor(Coord3D colorFace, Coord3D colorEdge) {
    this->colorFace = Coord3D(0, 0, 0);
    this->colorEdge = Coord3D(0, 0, 0);
    if(colorFace.getX() >= 0 && colorFace.getX() <= 255) {
        if(colorFace.getX() >= 0 && colorFace.getX() <= 255) {
            if(colorFace.getX() >= 0 && colorFace.getX() <= 255) {
                this->colorFace = colorFace;
            }
        }
    }

    if(colorEdge.getX() >= 0 && colorEdge.getX() <= 255) {
        if(colorEdge.getX() >= 0 && colorEdge.getX() <= 255) {
            if(colorEdge.getX() >= 0 && colorEdge.getX() <= 255) {
                this->colorEdge = colorEdge;
            }
        }
    }
}


void Face::applyColorFace() {
    glColor3d(colorFace.getX(), colorFace.getY(), colorFace.getZ());
}

void Face::applyColorEdge() {
    glColor3d(colorEdge.getX(), colorEdge.getY(), colorEdge.getZ());
}


void Face::removeVertex(int vertex) {
    vector<int>::iterator it(listVertex.begin());
    
    for (int i = 0; i < getSize(); i++) {
        if(listVertex[i] == vertex) {
            listVertex.erase(it);
            --it;
            i--;
        } else if(listVertex[i] > vertex) {
            listVertex[i] -= 1;
        }
        ++it;
    }
}





/*
void Face::drawFace() {
    glBegin(GL_POLYGON);
        glColor4d(colorFace.getX(), colorFace.getY(), colorFace.getZ(), 1);
        for(int i = 0; i < listVertex.size(); i++) {
            //printf("%f  %f %f\n", (*tabVertex[i]).getX(), (*tabVertex[i]).getY(), (*tabVertex[i]).getZ());
            glVertex3f((*tabVertex[i]).getX(),(*tabVertex[i]).getY(),(*tabVertex[i]).getZ());
        }
    glEnd();
}

void Face::drawEdge() {  
    glBegin(GL_LINES);
        glColor3d(colorEdge.getX(), colorEdge.getY(), colorEdge.getZ());
        for(int i = 0; i < tabVertex.size()-1; i++) {
            glVertex3f((*tabVertex[i]).getX(),(*tabVertex[i]).getY(),(*tabVertex[i]).getZ());
            glVertex3f((*tabVertex[i+1]).getX(),(*tabVertex[i+1]).getY(),(*tabVertex[i+1]).getZ());
        }
        glVertex3f((*tabVertex[tabVertex.size()-1]).getX(),(*tabVertex[tabVertex.size()-1]).getY(),(*tabVertex[tabVertex.size()-1]).getZ());
        glVertex3f((*tabVertex[0]).getX(),(*tabVertex[0]).getY(),(*tabVertex[0]).getZ());
    glEnd();
}

*/

string Face::toString() {
    string out = "<";
    for(int i = 0; i < listVertex.size(); i++) {
        std::ostringstream oss;
        oss << listVertex[i];
        out += oss.str();
        if(i != listVertex.size() - 1) {
            out += ", ";
        }
    }
    out += ">";
    return(out);
}