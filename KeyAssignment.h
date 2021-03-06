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
#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include "Camera.h"


class Controler;

using namespace std;

class KeyAssignment {
public:
    KeyAssignment();
    KeyAssignment(const KeyAssignment& orig);
    void chooseConfig();
    virtual ~KeyAssignment();
    void useKey(Event event, Controler* ctrl);
private:
    int* primary;
    vector<string> explode(const string& str, const char& ch);
    void readConfig();

};

#endif	/* KEYASSIGNMENT_H */

