/* 
 * File:   Object.cpp
 * Author: Administrator
 * 
 * Created on 29 octobre 2013, 11:12
 */

#include "Object.h"

Object::Object() {
}


Object::~Object() {
}

/* Ajout d'un sommet */
void Object::addVertex(Coord3D vertex) {
    this->listVertex.push_back(vertex);    
}

/* Suppression du sommet d'indice 'vertex' */
void Object::removeVertex(int vertex) {
    if(vertex < listVertex.size() && vertex >= 0) {
        /* Suppression de le tableau de sommets */
        vector<Coord3D>::iterator it(listVertex.begin());
        int i;
        for(i = 0; i < vertex; i++) {
            ++it;
        }
        this->listVertex.erase(it);
    
        /* Actualisation des faces */
        for(int i = 0; i < listFace.size(); i++) {
            for(int j = 0; j < listFace[i].size(); j++) {
                /*vector<Coord3D>::iterator it(listFace[i].begin());
                while (it != listVertex.end() && listVertex[i].equal(vertex)) {
                    ++i;
                }*/
            }
        }
    }
}

/* Suppression du sommet ayant les même valeurs que 'vertex' */
void Object::removeVertex(Coord3D vertex) {
    int i = 0;
    vector<Coord3D>::iterator it(listVertex.begin());
    while (it != listVertex.end() && listVertex[i].equal(vertex)) {
        ++i;
    }
    this->listVertex.erase(it);
}

/* AJout d'une face à partir d'une liste de sommets */
void Object::addFace(vector<int> tabVertex) {
    vector<int> face;
    
    for(int i = 0; i < tabVertex.size(); i++) {
        face.push_back(tabVertex[i]);
    }
    listFace.push_back(face);
}



void Object::drawFace() {
    glBegin(GL_POLYGON);
        glColor3d(255, 0, 0);
        for(int i = 0; i < listFace.size(); i++) {
            for(int j = 0; j < listFace[i].size(); j++) {
                glVertex3f(listVertex[listFace[i][j]].getX(), listVertex[listFace[i][j]].getY(), listVertex[listFace[i][j]].getZ());
            }
        }
    glEnd();
}


void Object::toString() {
    for(int i = 0; i < listVertex.size(); i++) {
        printf("(%f, %f, %f)\n", listVertex[i].getX(), listVertex[i].getY(), listVertex[i].getZ());
    }
    printf("\n");
}