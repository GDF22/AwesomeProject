/* 
 * File:   FrameManager.cpp
 * Author: Administrator
 * 
 * Created on 29 octobre 2013, 09:36
 */

#include "FrameManager.h"

FrameManager::FrameManager() {
    this->frameMax = 60;
    start = SDL_GetTicks();
    startfps = SDL_GetTicks();
}

FrameManager::FrameManager(int frameMax) {
    this->frameMax = frameMax;
    start = SDL_GetTicks();
    startfps = SDL_GetTicks();
}

FrameManager::~FrameManager() {
}


int FrameManager::getFrameMax() {
    return(this->frameMax);
}


int FrameManager::getFPS() {
    return(this->FPS);
}


void FrameManager::manageFrame() {
    current = SDL_GetTicks();
    
    while((current - start) < (1000 / (1.0*this->frameMax))) {
        current = SDL_GetTicks();
    }

    fpsTemp++;
    if(SDL_GetTicks() - startfps > 1000) {
        FPS = fpsTemp;
        fpsTemp = 0;
        startfps = SDL_GetTicks();
    }
    
    start = SDL_GetTicks();
}