/* 
 * File:   Event.h
 * Author: Administrator
 *
 * Created on 2 novembre 2013, 16:26
 */

#ifndef EVENT_H
#define	EVENT_H

#include <SDl/SDL.h>
#include <vector>

using namespace std;

class Event {
public:
    Event();
    virtual ~Event();
    
    bool EventManager();
    void removeKeyDown(SDLKey key);
    
    vector<SDLKey> notifyKeyboard();
    int* notifyMouse();
    pair<int,int> notifyClicked();
    
    int justDown();
    void initMousePosition();
private:
    int mouseX, mouseY, clickedX , clickedY;
    vector<SDLKey> listKeyDown;
    int justDownKey;
};

#endif	/* EVENT_H */

