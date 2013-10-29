/* 
 * File:   FrameManager.h
 * Author: Administrator
 *
 * Created on 29 octobre 2013, 09:36
 */

#ifndef FRAMEMANAGER_H
#define	FRAMEMANAGER_H

#include <SDL/SDL.h>
#include <ctime>
class FrameManager {
public:
    FrameManager();
    FrameManager(const FrameManager& orig);
    virtual ~FrameManager();
private:
    int frame;
    double fps;
    double update;
};

#endif	/* FRAMEMANAGER_H */

