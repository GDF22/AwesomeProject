/* 
 * File:   Button.cpp
 * Author: GDF
 * 
 * Created on 4 novembre 2013, 23:46
 */

#include "Button.h"
#include "Action.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <SDL/SDL.h>

using namespace std;

Button::Button() {
}

Button::Button(string name ,Coord3D cp , int width , int height, Color* color ,Action action) : Component(name){
    this->position = cp;
    this->width = width;
    this->height = height;
    this->c = color;
    this->visible = true;
    this->action = action;

}

Button::Button(const Button& orig) {
}

Button::~Button() {
}

void Button::draw(){
    if(isVisible()){
        if( c != NULL ){
            glBegin(GL_QUADS);
                glColor3ub(c->getR(), c->getG(), c->getB());
                glVertex2i(position.getX(), position.getY());
                glVertex2i(position.getX()+width, position.getY());
                glVertex2i(position.getX()+width, position.getY()+height);
                glVertex2i(position.getX(), position.getY()+height);
            glEnd();
        }  
    }
}

Action Button::getAction(){
    return action;
}