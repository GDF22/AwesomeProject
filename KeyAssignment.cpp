/* 
 * File:   KeyAssignment.cpp
 * Author: Administrator
 * 
 * Created on 31 octobre 2013, 22:49
 */

#include "KeyAssignment.h"
#include "Controler.h"
#include "Action.h"

KeyAssignment::KeyAssignment() {
    this->primary =  new int[20];
    //->readConfig();
    this->chooseConfig();
}

KeyAssignment::KeyAssignment(const KeyAssignment& orig) {
}

KeyAssignment::~KeyAssignment() {
}

void KeyAssignment::readConfig() {
    fstream file;
    string key = "";
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


void KeyAssignment::useKey(Event event, Controler* ctrl) {
    
    vector<SDLKey> currentKeys = event.notifyKeyboard();
    int justDown = event.justDown();
    
    // Touches enfoncees
    for(int i = 0; i < currentKeys.size(); i++) {
        if(currentKeys[i] == primary[0]) {
            ctrl->action(FORWARD);
        }
        if(currentKeys[i] == primary[1]) {
            ctrl->action(BACKWARD);
        }
        if(currentKeys[i] == primary[2]) {
            ctrl->action(LATERAL_LEFT);
        }
        if(currentKeys[i] == primary[3]) {
            ctrl->action(LATERAL_RIGHT);
        }
        if(currentKeys[i] == primary[4]) {
            ctrl->action(UP);
        }
        if(currentKeys[i] == primary[5]) {
            ctrl->action(DOWN);
        }
    }
    
    // Derniere touche pressee
    if(justDown != -1){
        if(justDown == SDLK_ESCAPE){
            ctrl->action(PAUSE_MENU);
        }
    }
    
    // Mouvements de la souris
    if(event.notifyMouse()[0] != 0 || event.notifyMouse()[1] != 0) {
        ctrl->action(UPDATEVIEW);
    }
    
    //click de la souris
 /*   if(event.notifyClicked().first != NULL){
        ctrl->actionOnClick(event.notifyClicked());
    }*/
}
