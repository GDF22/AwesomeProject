/* 
 * File:   KeyAssignment.cpp
 * Author: Administrator
 * 
 * Created on 31 octobre 2013, 22:49
 */

#include "KeyAssignment.h"

KeyAssignment::KeyAssignment() {
    this->primary =  new int[20];
    this->readConfig();
}

KeyAssignment::KeyAssignment(const KeyAssignment& orig) {
}

KeyAssignment::~KeyAssignment() {
}

void KeyAssignment::readConfig(){
    vector<string> keyVector; 
    printf("read2\n");
   
    
    /*
    FILE * pFile;
    pFile = fopen ("config/keys","w");
    */
    
        fstream myfile ("keys");
    
/*
    string value;
        if(pFile != NULL)  // si l'ouverture a réussi
        {       
                while ( fichier.good() )
                {
                     getline ( fichier, value, ';' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                     keyVector.push_back( value);
                     printf("\nvalue\n");
                     //cout << string( value, 1, value.length()-2 ); // display value removing the first and the last character from it
                }
            fichier.close();  // on ferme le fichier
        }
        else  // sinon
                cout << "Impossible d'ouvrir le fichier !" << endl;*/
}