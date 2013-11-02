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
    this->chooseConfig();
}

KeyAssignment::KeyAssignment(const KeyAssignment& orig) {
}

KeyAssignment::~KeyAssignment() {
}

void KeyAssignment::readConfig(){
    fstream file;
    string key;
    int count = 0 ;
    file.open("config\\keys");
    while (getline(file, key, ';')) {
      this->primary[count] = atoi(key.c_str() );
    }

}

void KeyAssignment::chooseConfig(){
    for(int i = 0 ; i < 4 ; i++){
        SDL_Event e;
        int tmpKey;
        while (SDL_WaitEvent(&e) && e.type != SDL_KEYDOWN ){
            tmpKey = e.key.keysym.sym;
        }
        cout<<tmpKey<<" - ";
        this->primary[i] = tmpKey;
    }
    
}
