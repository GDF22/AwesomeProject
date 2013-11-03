/* 
 * File:   KeyAssignment.h
 * Author: Administrator
 *
 * Created on 31 octobre 2013, 22:49
 */

#ifndef KEYASSIGNMENT_H
#define	KEYASSIGNMENT_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_getenv.h>
#include <vector>
#include <string>
#include "Camera.h"

using namespace std;

using namespace std; 
class KeyAssignment {
public:
    KeyAssignment();
    KeyAssignment(const KeyAssignment& orig);
    void chooseConfig();
    virtual ~KeyAssignment();
    void useKey(vector<SDLKey> keys, Camera* camera);
private:
    int* primary;
    vector<string> explode(const string& str, const char& ch);
    void readConfig();

};

#endif	/* KEYASSIGNMENT_H */

