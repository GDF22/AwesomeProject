/* 
 * File:   Button.h
 * Author: GDF
 *
 * Created on 4 novembre 2013, 23:46
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <string>
#include "Coord3D.h"
#include "Color.h"
#include "Component.h"
#include "Action.h"
#include <sstream>

using namespace std;

class Button : public Component {
public:
    Button();
    Button(string name ,Coord3D cp , int width , int height, Color* color, Action action);
    Button(const Button& orig);
    virtual ~Button();
    void draw();
    Action getAction();
private:
    SDL_Surface* sdlPanel;
    Color* c;
    Action action;
};

#endif	/* BUTTON_H */

