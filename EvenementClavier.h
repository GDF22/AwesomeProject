/* 
 * File:   EvenementClavier.h
 * Author: Administrator
 *
 * Created on 19 octobre 2013, 14:01
 */

#ifndef EVENEMENTCLAVIER_H
#define	EVENEMENTCLAVIER_H

#include <map> 
#include <iostream>
#include <string>
#include <cstdio> 
#include<SDL/SDL.h>

/*struct classcomp {
  bool operator() (const std::string& lhs, const std::string& rhs) const
  {return lhs<rhs;}
};*/

class EvenementClavier {
public:
    EvenementClavier();
    
    void gereEvent(SDL_Event event);
    
    //std::map<std::string, int, classcomp> getTabKey();
    int get(std::string key);
    
    //std::map<std::string, int> tabKey;
    bool up, down, left, right, k8, k4, k6, k2;
    int sourisdx, sourisdy, wheel;
    
    private:
};

#endif	/* EVENEMENTCLAVIER_H */

