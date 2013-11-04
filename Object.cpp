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
        /* Suppression dans le tableau de sommets */
        vector<Coord3D>::iterator it(listVertex.begin());
        for(int i = 0; i < vertex; i++) {
            ++it;
        }
        this->listVertex.erase(it);

        actualisationFace(vertex);
    }
}

/* Suppression du sommet ayant les même valeurs que 'vertex' */
void Object::removeVertex(Coord3D vertex) {
    bool found = false;
    int i = 0;
    vector<Coord3D>::iterator it(listVertex.begin());
    
    /* Suppression dans le tableau de sommets */
    while (it != listVertex.end() && !found) {
        if(listVertex[i].equal(vertex)) {
            found = true;
        } else {
            ++it;
            i++;
        }
    }
    if(found) {
        this->listVertex.erase(it);
    }
    
    actualisationFace(i);
}

void Object::actualisationFace(int vertex) {
    // Suppression du vertex dans toutes les faces
    for(int i = 0; i < listFace.size(); i++) {
        listFace[i].removeVertex(vertex);
    }
    
    // Suppression des faces ayant moins de 2 sommets
    vector<Face>::iterator it(listFace.begin());
    for(int i = 0; i < listFace.size(); i++) {
        if(listFace[i].getSize() <= 1) {
            listFace.erase(it);
            ++it;
        }
    }
}




/* AJout d'une face à partir d'une liste de sommets */
void Object::addFace(vector<int> listVertex, Color* colorFace, Color* colorEdge) {
    Face* face = new Face(listVertex);
    face->setColorFace(colorFace);
    face->setColorEdge(colorEdge);
    listFace.push_back(*face);
}

/* AJout d'une face à partir d'une face */
void Object::addFace(Face* face) {
    listFace.push_back(*face);
}


/* Affichage des faces */
void Object::drawFace() {
    for(int i = 0; i < listFace.size(); i++) {
        glBegin(GL_POLYGON);
            listFace[i].applyColorFace();
            for(int j = 0; j < listFace[i].getSize(); j++) {
                Coord3D vertex = listVertex[listFace[i].getVertex(j)];
                glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
            }
         glEnd();
    }
}

/* Affichage des arêtes */
void Object::drawEdge() {
    Coord3D vertex1, vertex2;
    
    glBegin(GL_LINES);
        for(int i = 0; i < listFace.size(); i++) {
            listFace[i].applyColorEdge();
            for(int j = 0; j < listFace[i].getSize() - 1; j++) {
                vertex1 = listVertex[listFace[i].getVertex(j)];
                vertex2 = listVertex[listFace[i].getVertex(j+1)];
                glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
                glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
            }
            vertex1 = listVertex[listFace[i].getVertex(listFace[i].getSize()- 1)];
            vertex2 = listVertex[listFace[i].getVertex(0)];
            glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
            glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
        }
    glEnd();
}


int Object::nbVertex() {
    return(listVertex.size());
}


int Object::nbFace() {
    return(listFace.size());
}


string Object::toString() {
    string out = "";
    /*for(int i = 0; i < listVertex.size(); i++) {
        out += listVertex[i].toString() + "\n";
    }*/
    for(int i = 0; i < listFace.size(); i++) {
        out += listFace[i].toString() + "\n";
    }
    return(out);
}