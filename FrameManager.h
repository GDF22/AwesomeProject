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
    FrameManager(int frameMax);
    virtual ~FrameManager();
    
    void manageFrame();
    int getFrameMax();
    int getFPS();
private:
    int frameMax;
    int FPS;
    int fpsTemp;
    double startfps;
    double start;
    double current;
};

#endif	/* FRAMEMANAGER_H */

