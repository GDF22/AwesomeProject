/* 
 * File:   World.cpp
 * Author: Administrator
 * 
 * Created on 3 novembre 2013, 14:34
 */

#include "World.h"

bool ReadLine(ifstream *file, char *firstChar, vector<double> *listNb);

World::World() {
    string file = "suzanne.obj";
    addObject(file);
    listObject[0].setPosition(new Coord3D(5, -3, 4));
    listObject[0].rotate(M_PI/2, 0, 0);
    listObject[0].rotate(0, -M_PI/2, 0);
    
    addObject(listObject[0]);
    listObject[0].setPosition(new Coord3D(4, -2, 2));
    listObject[0].rotate(M_PI*3.5, 0, 0);
    
    addObject(listObject[0]);
    listObject[0].setPosition(new Coord3D(0, -1, 1));
    listObject[0].rotate(M_PI, 0, 0);
    
    addObject(listObject[0]);
    listObject[0].setPosition(new Coord3D(2, 3, 4));
    listObject[0].rotate(M_PI/2, 0, 0);
}

World::World(const World& orig) {
}

World::~World() {
}


void World::addObject(Object obj) {
    listObject.push_back(obj);
}

bool World::addObject(string filename) {
    ifstream file(filename.c_str(), ios::in);
	if(!file) {
        cout << "Impossible d'ouvrir " << filename << endl;
        return false;
    }
    
    Object newObject;
	Coord3D pt3D;
    char firstChar;
    vector<double> listNb;
    vector<int> listInt;
    
    while(ReadLine(&file, &firstChar, &listNb)) {
        if(firstChar == '#') {	// on a trouvé un commentaire, on passe
        } else if(firstChar == 'v') {	// on a trouvé une vertice ?
            pt3D = Coord3D(listNb[0], listNb[1], listNb[2]);
            newObject.addVertex(Coord3D(pt3D));
        } else if(firstChar == 'f') {	// on a trouvé une face
            Color f(255, 0, 0);
            Color e(255, 255, 255);
            listInt.clear();
            for(int i = 0; i < listNb.size(); i++) {
                listInt.push_back((int)listNb[i]-1);
            }
            newObject.addFace(listInt, new Color(180, 180, 180), new Color(255, 255, 255)); // on enregistre la face récupérée
		}
		listNb.clear();
	}
	file.close();
	listObject.push_back(newObject);
    
    return(true);
}

void World::removeObject(Object obj) {
    
}

void World::removeObject(int obj) {
    vector<Object>::iterator it(listObject.begin());
    for(int i = 0; i < obj; i++) {
        ++it;
    }
    listObject.erase(it);
}



void World::draw() {
    for(int i = 0; i < listObject.size(); i++) {
        listObject[i].rotate(0.1, 0, 0);
        listObject[i].drawFace();
        listObject[i].drawEdge();
    }
}


bool ReadLine(ifstream *file, char *firstChar, vector<double> *listNb) {	// Lecture d'une ligne de texte dans un fichier
    int nb;
    char c;
    string s = "";

    file->get(*firstChar);
    if(!file->eof()) {   // Si la fin du fichier n'a pas été atteinte
        if(*firstChar == '#') {  // S'il ne s'agit pas d'un commentaire
            while(c != '\n') {
                file->get(c);
            }
            return(true);
        }
        
        file->get(c);   // On lit le caractère suivant (espace)
        file->get(c);
        while(c != '\n') {  // Tant que ce caractère n'est pas une fin de ligne
            if(c != ' ') {   // Tant que ce caractère n'est pas un espace
                s += c;     // On ajoute ce caractère à s
            } else {
                listNb->push_back(::atof(s.c_str()));
             //   cout << (*listNb)[listNb->size()-1] << endl;
                s = "";
            }
            file->get(c);
        }
        listNb->push_back(::atof(s.c_str()));
        return (true);
    }
    
    return(false);
}