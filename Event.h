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
    
    void EventManager();
    void removeKeyDown(SDLKey key);
    
    vector<SDLKey> notifyKeyboard();
    int* notifyMouse();
private:
    int mouseX, mouseY;
    vector<SDLKey> listKeyDown;
};

#endif	/* EVENT_H */

