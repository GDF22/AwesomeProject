/* 
 * File:   Event.h
 * Author: Administrator
 *
 * Created on 2 novembre 2013, 16:26
 */

#ifndef EVENT_H
#define	EVENT_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

using namespace std;

class Event {
public:
    Event();
    virtual ~Event();
    
    bool EventManager();
    void removeKeyDown(SDL_Keycode key);
    
    vector<SDL_Keycode> notifyKeyboard();
    int* notifyMouse();
    pair<int,int> notifyClicked();
    
    int justDown();
    void initMousePosition(SDL_Window* pWindow);
private:
    int mouseX, mouseY, clickedX , clickedY;
    vector<SDL_Keycode> listKeyDown;
    int justDownKey;
};

#endif	/* EVENT_H */

