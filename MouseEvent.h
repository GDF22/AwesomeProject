/* 
 * File:   MouseEvent.h
 * Author: Administrator
 *
 * Created on 28 octobre 2013, 19:04
 */

#ifndef MOUSEEVENT_H
#define	MOUSEEVENT_H

#include <SDL/SDL.h>

class MouseEvent {
public:
    MouseEvent();
    virtual ~MouseEvent();
    void EventManager(SDL_Event event);
    
    int sourisdx, sourisdy, wheel;
private:

};

#endif	/* MOUSEEVENT_H */

