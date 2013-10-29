/* 
 * File:   KeyboardEvent.h
 * Author: Administrator
 *
 * Created on 28 octobre 2013, 18:59
 */

#ifndef KEYBOARDEVENT_H
#define	KEYBOARDEVENT_H

#include <SDL/SDL.h>

class KeyboardEvent {
public:
    KeyboardEvent();
    virtual ~KeyboardEvent();
    void EventManager(SDL_Event event);
    
    bool up, down, left, right, k8, k4, k6, k2;
private:
};

#endif	/* KEYBOARDEVENT_H */

