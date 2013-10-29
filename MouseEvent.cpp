/* 
 * File:   MouseEvent.cpp
 * Author: Administrator
 * 
 * Created on 28 octobre 2013, 19:04
 */

#include "MouseEvent.h"

MouseEvent::MouseEvent() {
    sourisdx = 0;
    sourisdy = 0;
    wheel = 0;
}


MouseEvent::~MouseEvent() {
}


void MouseEvent::EventManager(SDL_Event event) {
    int centrex = 800;
    int centrey = 450;
    int x, y;
    sourisdx = 0;
    sourisdy = 0;
    wheel = 0;
    
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_WHEELDOWN:
                wheel--;
                break;
            case SDL_BUTTON_WHEELUP:
                wheel++;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            x = event.button.x;
            y = event.button.y;

            sourisdx = centrex - x;
            sourisdy = centrey - y;
            break;
    }
}