/* 
 * File:   Event.cpp
 * Author: Administrator
 * 
 * Created on 2 novembre 2013, 16:26
 */

#include "Event.h"

Event::Event() {
}


Event::~Event() {
}


bool Event::EventManager() {
    int centrex = 800;
    int centrey = 450;
    
    SDL_Event event;
    SDL_PollEvent(&event);
    justDownKey = -1;
    switch(event.type) {
        case SDL_QUIT:
            return(false);
            break;
        case SDL_KEYDOWN:
            listKeyDown.push_back(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            justDownKey = event.key.keysym.sym;
            removeKeyDown(event.key.keysym.sym);
            break;
        /*case SDL_MOUSEBUTTONDOWN:
            listKeyDown.push_back(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            removeKeyDown(event.button.button);
            break;*/
        case SDL_MOUSEMOTION:
            mouseX = centrex - event.button.x;
            mouseY = centrey - event.button.y;
            break;
    }
    
    SDL_WarpMouse(800, 450);
    return(true);
}


void Event::removeKeyDown(SDLKey key) {
    vector<SDLKey>::iterator it(listKeyDown.begin());
    for(int i = 0; i < listKeyDown.size(); i++) {
        if(listKeyDown[i] == key) {
            listKeyDown.erase(it);
        }
        ++it;
    }
}


vector<SDLKey> Event::notifyKeyboard() {
    return(listKeyDown);
}

int Event::justDown(){
    return(justDownKey);
}

int* Event::notifyMouse() {
    int* mouse = new int[2];
    mouse[0] = mouseX;
    mouse[1] = mouseY;
    mouseX = 0;
    mouseY = 0;
    
    return(mouse);
}