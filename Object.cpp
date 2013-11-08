/* 
 * File:   Object.cpp
 * Author: Administrator
 * 
 * Created on 29 octobre 2013, 11:12
 */

#include "Object.h"

using namespace std;

Object::Object() {
    name = "noname";
    position = new Coord3D(0, 0, 0);
}

Object::Object(string name, Coord3D* position) {
    this->name = name;
    this->position = position;
}

Object::~Object() {
}



Coord3D* Object::getPosition() {
    return(this->position);
}

void Object::setPosition(Coord3D* position) {
    this->position = position;
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


void Object::rotate(double rotH, double rotV, double rotJSPQ) {
    for(int i = 0 ; i < listVertex.size(); i++) {
        rotateHorizontal(&(listVertex[i]), rotH);
        rotateVertical(&(listVertex[i]), rotV);
    }
}

void Object::rotateHorizontal(Coord3D* vertex, double rotation) {
    double distance = sqrt(pow(vertex->getX(), 2) + pow(vertex->getY(), 2));
    double angle = 0;
    double dx, dy;
    dx = vertex->getX();
    dy = vertex->getY();

    if(dx == 0 || dy == 0) {
        angle = 0;
    } else if((dx >= 0 && dy > 0) || (dx <= 0 && dy < 0)) {		// Calcul de l'angle
        angle = atan(abs(dy) / abs(dx));
    } else {
        angle = atan(abs(dx) / abs(dy));
    }
    
    // Orientation de l'angle sur le cercle trigo
    if(dx <= 0 && dy > 0) {
        angle += M_PI/2;
    }
    if(dx < 0 && dy <= 0) {
        angle += M_PI;
    }
    if(dx >= 0 && dy < 0) {
        angle += M_PI*1.5;
    }
    
    *vertex = Coord3D(cos(angle + rotation)*distance, sin(angle + rotation)*distance, vertex->getZ());
}


void Object::rotateVertical(Coord3D* vertex, double rotation) {
    double distance = sqrt(pow(vertex->getX(), 2) + pow(vertex->getZ(), 2));
    double angle = 0;
    double dx, dy;
    dx = vertex->getX();
    dy = vertex->getZ();

    if(dx == 0 || dy == 0) {
        angle = 0;
    } else if((dx >= 0 && dy > 0) || (dx <= 0 && dy < 0)) {		// Calcul de l'angle
        angle = atan(abs(dy) / abs(dx));
    } else {
        angle = atan(abs(dx) / abs(dy));
    }
    
    // Orientation de l'angle sur le cercle trigo
    if(dx <= 0 && dy > 0) {
        angle += M_PI/2;
    }
    if(dx < 0 && dy <= 0) {
        angle += M_PI;
    }
    if(dx >= 0 && dy < 0) {
        angle += M_PI*1.5;
    }
    
    *vertex = Coord3D(cos(angle + rotation)*distance, vertex->getY(), sin(angle + rotation)*distance);
}




/* Affichage des faces */
void Object::drawFace() {
    for(int i = 0; i < listFace.size(); i++) {
        glBegin(GL_POLYGON);
            listFace[i].applyColorFace();
            for(int j = 0; j < listFace[i].getSize(); j++) {
                Coord3D vertex = listVertex[listFace[i].getVertex(j)] + *(this->position);
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
                vertex1 = listVertex[listFace[i].getVertex(j)] + *(this->position);
                vertex2 = listVertex[listFace[i].getVertex(j+1)] + *(this->position);
                glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
                glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
            }
            vertex1 = listVertex[listFace[i].getVertex(listFace[i].getSize()- 1)] + *(this->position);
            vertex2 = listVertex[listFace[i].getVertex(0)] + *(this->position);
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
    string out = this->name + " : ";
    for(int i = 0; i < listFace.size(); i++) {
        out += listFace[i].toString() + "\n";
    }
    return(out);
}