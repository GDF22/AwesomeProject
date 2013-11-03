/* 
 * File:   KeyAssignment.cpp
 * Author: Administrator
 * 
 * Created on 31 octobre 2013, 22:49
 */

#include "KeyAssignment.h"

KeyAssignment::KeyAssignment() {
    this->primary =  new int[20];
    //this->readConfig();
    this->chooseConfig();
}

KeyAssignment::KeyAssignment(const KeyAssignment& orig) {
}

KeyAssignment::~KeyAssignment() {
}

void KeyAssignment::readConfig() {
    fstream file;
    string key;
    int count = 0 ;
    file.open("config\\keys");
    while (getline(file, key, ';')) {
      this->primary[count] = atoi(key.c_str() );
    }
}

void KeyAssignment::chooseConfig(){
    int i = 0;
    SDL_Event e;
    while(i < 6) {
      SDL_WaitEvent(&e);
      if(e.type == SDL_KEYDOWN) {
          this->primary[i] = e.key.keysym.sym;
          i++;
      }
    }
}


void KeyAssignment::useKey(vector<SDLKey> keys, Camera* camera) {
    for(int i = 0; i < keys.size(); i++) {
        if(keys[i] == primary[0]) {
            camera->forward();
        }
        if(keys[i] == primary[1]) {
            camera->backward();
        }
        if(keys[i] == primary[2]) {
            camera->lateralLeft();
        }
        if(keys[i] == primary[3]) {
            camera->lateralRight();
        }
        if(keys[i] == primary[4]) {
            camera->up();
        }
        if(keys[i] == primary[5]) {
            camera->down();
        }
    }
}
