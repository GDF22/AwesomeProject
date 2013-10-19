/* 
 * File:   EvenementClavier.cpp
 * Author: Administrator
 * 
 * Created on 19 octobre 2013, 14:01
 */

#include "EvenementClavier.h"

#include <map> 
#include <iostream>
#include <string>
#include <cstdio> 

EvenementClavier::EvenementClavier() {
    /*tabKey['a'] = 0;
    tabKey["DOWN"] = false;
    tabKey["LEFT"] = false;
    tabKey["RIGHT"] = false;
    tabKey["KP2"] = false;
    tabKey["KP4"] = false;
    tabKey["KP6"] = false;
    tabKey["KP8"] = false;*/

    up = false;
    down = false;
    left = false;
    right = false;
    k8 = false;
    k4 = false;
    k6 = false;
    k2 = false;
}


/*std::map<std::string, int, classcomp> EvenementClavier::getTabKey() {
    return(tabKey);
}*/

/*int EvenementClavier::get(std::string key) {
    return(tabKey[key]);
}*/


void EvenementClavier::gereEvent(SDL_Event event) {
    switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        left = true;
                        break;
                    case SDLK_RIGHT:
                        right = true;
                        break;
                    case SDLK_UP:
                        up = true;
                        break;
                    case SDLK_DOWN:
                        down = true;
                        break;
                    case SDLK_KP4:
                        k4 = true;
                        break;
                    case SDLK_KP6:
                        k6 = true;
                        break;
                    case SDLK_KP8:
                        k8 = true;
                        break;
                    case SDLK_KP2:
                        k2 = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        left = false;
                        break;
                    case SDLK_RIGHT:
                        right = false;
                        break;
                    case SDLK_UP:
                        up = false;
                        break;
                    case SDLK_DOWN:
                        down = false;
                        break;
                    case SDLK_KP4:
                        k4 = false;
                        break;
                    case SDLK_KP6:
                        k6 = false;
                        break;
                    case SDLK_KP8:
                        k8 = false;
                        break;
                    case SDLK_KP2:
                        k2 = false;
                        break;
                }
                break;
        }
}