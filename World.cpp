/* 
 * File:   World.cpp
 * Author: Administrator
 * 
 * Created on 3 novembre 2013, 14:34
 */

#include "World.h"

char * ReadLine(FILE *fp);

World::World() {
    char* file = "untitled.obj";
    addObject(file);
}

World::World(const World& orig) {
}

World::~World() {
}


void World::addObject(Object obj) {
    listObject.push_back(obj);
}

bool World::addObject(char* filename) {
    Object newObject;
    FILE *fp = fopen(filename,"rb");
	if(!fp) return false;
    
	Face face;
	Coord3D pt3D;
	Coord3D pt2D;
	char *buf,buftmp[64];
	long i,v,g;	// compteur pour le stockage des données lors de la seconde passe
	unsigned int lenbuf;
    
    cout << "coucou" << endl;
	while (!feof(fp)) {
		buf = ReadLine(fp);
		lenbuf = strlen((const char *)buf);
		if (lenbuf > 0) {
			sscanf(buf,"%s",buftmp);
            
			if(!strcmp((const char *)buftmp,"#")) {	// on a trouvé un commentaire, on passe
                cout << "yop" << endl;
			} else if(!strcmp((const char *)buftmp,"v")) {	// on a trouvé une vertice ?
				//sscanf(&buf[2],"%f%f%f",&pt3D.x,&pt3D.y,&pt3D.z);
                cout << "v" << endl;
                pt3D = Coord3D(sscanf(buf,"%f"), sscanf(buf,"%f"), sscanf(buf,"%s"));
				newObject.addVertex(Coord3D(pt3D));
			} else if(!strcmp((const char *)buftmp,"f")) {	// on a trouvé une face
				cout << "f" << endl;
                for(i=0; (buf[i] < '0') || (buf[i] > '9') ;i++);	// on se positionne à la première valeur
                vector<int> vect;
				for(v=0; v < 4 ;v++) { // triangles donc composés de 3 vertices
					vect.push_back(sscanf(buf,"%f"));
				}
				newObject.addFace(Face(vect, Color(1, 0, 0), Color(1, 1, 1))); // on enregistre la face récupérée
			}
		}
		delete[] buf;
	}
    cout << "coucou2" << endl;
	fclose(fp);
	listObject.push_back(newObject);
    cout << "new" << endl;
    return true;
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
        cout << i << endl;
        listObject[i].drawFace();
    }
}


char * ReadLine(FILE *fp) {	// Lecture d'une ligne de texte dans un fichier
	bool extract = true;
	char *buffer = new char[1024];
	int i = 0;

	buffer[0]=0;
	while (extract && !feof(fp)) {
		if (fread(&buffer[i],1,1,fp) > 0) {
			if(buffer[i]==0x0D) {
				fread(&buffer[i],1,1,fp);
				if(buffer[i]==0x0A) {
					buffer[i] = 0;
					extract = false;
				} else {
					i++;
				}
			} else {
				i++;
			}
		}
	}
    for(int i = 0; i < 300; i++) {
        cout << buffer[i];
    }
    cout << endl << endl << endl;
	return buffer;
}