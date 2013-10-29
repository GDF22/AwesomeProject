/* 
 * File:   KeyboardEvent.cpp
 * Author: Administrator
 * 
 * Created on 28 octobre 2013, 18:59
 */

#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() {
    up = false;
    down = false;
    left = false;
    right = false;
    k8 = false;
    k4 = false;
    k6 = false;
    k2 = false;
}


KeyboardEvent::~KeyboardEvent() {
}


void KeyboardEvent::EventManager(SDL_Event event) {
    switch(event.type) {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    exit(0);
                    break;
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